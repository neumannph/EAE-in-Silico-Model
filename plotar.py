import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 

nome_arquivo = 'Dados.csv'
colunas = ['Tempo', 'Células Iba-1+ (micróglias)', 'Citocinas Pró-Inflamatórias', 'Oligodendrócitos']

try:
    df = pd.read_csv(nome_arquivo, sep=r'\s+', header=None)
    
    df.columns = colunas
    
except FileNotFoundError:
    print(f"Erro: Arquivo '{nome_arquivo}' não encontrado.")
    exit()
except Exception as e:
    print(f"Erro ao ler o arquivo: {e}")
    exit()

# Configurações de fonte
plt.rcParams.update({
    'font.family': 'serif', 
    'font.serif': ['Times New Roman'],
})

# Plotagem 

plt.figure(figsize=(16, 9)) 

# Plota as Células Iba-1+ (micróglias)
plt.plot(df['Tempo'], df['Células Iba-1+ (micróglias)'], label='Células Iba-1+ (micróglias)', linewidth=3)

# Plota as Citocinas Pró-Inflamatórias
plt.plot(df['Tempo'], df['Citocinas Pró-Inflamatórias'], label='Citocinas Pró-Inflamatórias', linewidth=3)

# Plota os Oligodendrócitos
plt.plot(df['Tempo'], df['Oligodendrócitos'], label='Oligodendrócitos', linewidth=3)


# Configurações Visuais
plt.title('Simulação gráfica do sistema de equações', fontsize = 27, fontweight='bold', pad=20)
plt.xlabel('Tempo (dias)', fontsize = 27, fontweight='bold', labelpad = 15)
plt.ylabel('Densidade / Concentração', fontsize = 27, fontweight='bold', labelpad = 20)
plt.grid(True, linestyle='--', alpha=0.9) 
plt.legend(fontsize = 25) 
plt.yticks(fontsize = 25)
plt.xticks(fontsize = 25)
plt.tight_layout()

plt.tight_layout() 
plt.savefig('gráfico.jpg') 
plt.show()