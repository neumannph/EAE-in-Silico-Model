import numpy as np
import pandas as pd
import subprocess
import warnings
from SALib.sample import sobol
from SALib.analyze import sobol as analyze_sobol

# 1. Definição do Problema (13 parâmetros)
problem = {
    'num_vars': 13,
    'names': [
        'microglia', 'oligod', 'delta', 'lambda', 'ni', 'p',
        'gamma', 'beta', 'alpha', 'mi', 'kappa', 'citoP', 'citoA'
    ],
    'bounds': [[0.5, 1.5] for _ in range(13)]
}

# 2. Amostragem de Sobol (lembre-se de mudar para N=2**17 no rodizio final)
param_values = sobol.sample(problem, N=2**17)
print(f"Total de simulações a executar: {len(param_values)}")

# 3. Execução das simulações salvando a série temporal diretamente em CSV
def rodar_simulacoes(amostras):
    y_final = np.zeros((len(amostras), 7))
    
    # Abre o CSV para salvar todos os passos de tempo de todas as simulações
    with open('serie_temporal_completa.csv', 'w') as f_out:
        # Escreve o cabeçalho
        f_out.write("tempo_t,Micróglia_Homeostatica,Micróglia_Ativa,Oligodendrócitos,Citocina_Pro,Citocina_Anti,Micróglia_Total\n")
        
        for i, p in enumerate(amostras):
            args_cpp = [str(val) for val in p]
            
            # Chama o binário compilado
            resultado = subprocess.run(
                ['./rodatudo'] + args_cpp,
                capture_output=True,
                text=True
            )
            
            linhas = resultado.stdout.strip().split('\n')
            
            # Escreve cada passo de tempo no arquivo CSV com a ID da simulação
            for linha in linhas:
                if linha.strip():
                    f_out.write(f"{linha}\n")
            
            # Pega o último passo de tempo da simulação para a análise de Sobol
            ultima_linha = [float(v) for v in linhas[-1].split(',')]
            # reordena para manter (x0, x1, x2, x3, x4, x5, t)
            y_final[i, :] = ultima_linha[1:] + [ultima_linha[0]]
            
            if (i + 1) % 50000 == 0 or (i + 1) == len(amostras):
                print(f"Progresso: {i + 1}/{len(amostras)} simulações concluídas...")
                
    return y_final

# Executa as simulações
Y_final = rodar_simulacoes(param_values)

# 4. Salvar Matriz de Parâmetros e Respostas Finais
np.savetxt('param_values.csv', param_values, delimiter=',', header=','.join(problem['names']), comments='')
np.savetxt('resultados_Y_final.csv', Y_final, delimiter=',', header='Micróglia Homeostatica,Micróglia Ativa,Oligodendrócitos,Citocina Pro,Citocina Anti,Micróglia Total,Tempo', comments='')

# 5. Cálculo e Salvamento dos Índices de Sensibilidade de Sobol (Apenas para as 6 variáveis biológicas)
nomes_saidas = ['Micróglia Homeostatica', 'Micróglia Ativa', 'Oligodendrócitos', 'Citocina Pro', 'Citocina Anti', 'Micróglia Total']

# Y_final.T[:6] ignora a 7ª coluna (Tempo)
with warnings.catch_warnings():
    warnings.simplefilter("ignore", category=RuntimeWarning)
    Si = [analyze_sobol.analyze(problem, x) for x in Y_final.T[:6]]

df_s1 = pd.DataFrame({nomes_saidas[idx]: s['S1'] for idx, s in enumerate(Si)}, index=problem['names'])
df_st = pd.DataFrame({nomes_saidas[idx]: s['ST'] for idx, s in enumerate(Si)}, index=problem['names'])

# Tratamento para remover valores negativos do ruído estatístico e eventuais NaNs
df_s1 = df_s1.fillna(0.0).clip(lower=0.0)
df_st = df_st.fillna(0.0).clip(lower=0.0)

df_s1.to_csv('sobol_S1.csv')
df_st.to_csv('sobol_ST.csv')

