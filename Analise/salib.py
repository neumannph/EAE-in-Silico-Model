import numpy as np
import subprocess
from SALib.sample import sobol
from SALib.analyze import sobol as analyze_sobol
import matplotlib.pyplot as plt
import pickle

# 1. Definição do Problema (13 parâmetros)
problem = {
    'num_vars': 13,
    'names': [
        'microglia', 'oligod', 'delta', 'lambda', 'ni', 'p',
        'gamma', 'beta', 'alpha', 'mi', 'kappa', 'citoP', 'citoA'
    ],
    'bounds': [[0.5, 1.5] for _ in range(13)]
}


# 2. Amostragem de Sobol
param_values = sobol.sample(problem, N=2**17)
print(f"Total de simulações a executar: {len(param_values)}")

# 3. Execução das simulações chamando o binário C++
def rodar_simulacao_cpp(amostras):
    y = np.zeros((len(amostras), 6))
    
    for i, p in enumerate(amostras):
        args_cpp = [str(val) for val in p]
        
        # Executa o programa ./model na mesma pasta
        resultado = subprocess.run(
            ['./rodatudo'] + args_cpp,
            capture_output=True,
            text=True
        )
        
        # Converte a saída impressa pelo C++ (std::cout) em float
        valores = [float(val) for val in resultado.stdout.strip().split()]
        y[i, :] = valores
      
        
        if (i + 1) % 1000 == 0:
            print(f"Progresso: {i + 1}/{len(amostras)} simulações concluídas...")
            
    return y

# Executa o lote de testes
Y = rodar_simulacao_cpp(param_values)
# 4. Cálculo dos Índices de Sensibilidade
Si = [analyze_sobol.analyze(problem, x) for x in Y.T]

np.save('param_values.npy', param_values)
np.save('resultados_Y.npy', Y)
with open('sobol_indices.pkl', 'wb') as f:
    pickle.dump(Si, f)
# Exibição dos resultados
'''print("\n--- Sensibilidade de Primeira Ordem (S1) [Efeito isolado] ---")
for name, s1 in zip(problem['names'], Si['S1']):
    print(f"{name:10s}: {s1}")

print("\n--- Sensibilidade Total (ST) [Efeito com interações] ---")
for name, st in zip(problem['names'], Si['ST']):
    print(f"{name:10s}: {st}")'''