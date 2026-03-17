import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 

nome_arquivo = 'Dados.csv'
colunas = ['Tempo', 'Células Iba-1+ (micróglias)', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias']

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

fig, ax = plt.subplots(1,2, figsize = (12, 5))

# Plota as Células Iba-1+ (micróglias)
ax[0].plot(df['Tempo'], df['Células Iba-1+ (micróglias)'], label='Células Iba-1+ (micróglias)', linewidth=3, color = 'tab:red')

# Plota os Oligodendrócitos
ax[0].plot(df['Tempo'], df['Oligodendrócitos'], label='Oligodendrócitos', linewidth=3, color = 'tab:green')

# Configurações Visuais
ax[0].set_title('Simulação gráfica do sistema de equações', fontsize = 11, fontweight='bold')
ax[0].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
ax[0].set_ylabel('Densidade', fontsize = 11, fontweight='bold')
ax[0].grid(True) 
ax[0].legend(fontsize = 13) 
ax[0].tick_params(labelsize = 13)

# Plota as Citocinas Pró-Inflamatórias
ax[1].plot(df['Tempo'], df['Citocinas Pró-Inflamatórias'], label='Citocinas Pró-Inflamatórias', linewidth=3, color = 'tab:orange')

# Plota as Citocinas Anti-Inflamatórias
ax[1].plot(df['Tempo'], df['Citocinas Anti-Inflamatórias'], label='Citocinas Anti-Inflamatórias', linewidth=3, color = 'tab:blue')

# Configurações Visuais
ax[1].set_title('Simulação gráfica do sistema de equações', fontsize = 11, fontweight='bold')
ax[1].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
ax[1].set_ylabel('Concentração', fontsize = 11, fontweight='bold')
ax[1].grid(True) 
ax[1].legend(fontsize = 13) 
ax[1].tick_params(labelsize = 13)

plt.tight_layout() 
plt.savefig('gráfico.jpg') 
plt.show()