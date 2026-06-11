import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 

arquivo = 'dados.csv'
colunas = ['Tempo', 'Micróglias', 'Células Iba-1+', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias']

try:
    df = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
    
    df.columns = colunas
    
except FileNotFoundError:
    print(f"Erro: Arquivo '{arquivo}' não encontrado.")
    exit()
except Exception as e:
    print(f"Erro ao ler o arquivo: {e}")
    exit()

# Configurações de fonte
plt.rcParams.update({
    'font.family': 'serif', 
    'font.serif': ['Times New Roman'],
})

print("============= PICOS =============")

tempo = df['Tempo'].to_numpy()
microglias = df['Micróglias'].to_numpy()
celulasIba1 = df['Células Iba-1+'].to_numpy()
oligodendrocitos = df['Oligodendrócitos'].to_numpy()
citocinaPro = df['Citocinas Pró-Inflamatórias'].to_numpy()
citocinaAnti = df['Citocinas Anti-Inflamatórias'].to_numpy()

# Microglias
valorPico = np.max(microglias)
indicePico = np.argmax(microglias)
tempoPico = tempo[indicePico]
print(f"Microglias: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

# Celulas Iba-1+
valorPico = np.max(celulasIba1)
indicePico = np.argmax(celulasIba1)
tempoPico = tempo[indicePico]
print(f"Celulas Iba1+: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

# Oligodendrócitos
valorMin = np.min(oligodendrocitos)
indiceMin = np.argmin(oligodendrocitos)
tempoMin = tempo[indiceMin]
print(f"Oligodendrócitos: {valorMin} cells/mm² (valor mínimo) - Tempo: {tempoMin} dias")

# Citocinas Pró-Inflamatórias
valorPico = np.max(citocinaPro)
indicePico = np.argmax(citocinaPro)
tempoPico = tempo[indicePico]
print(f"Citocinas Pró-Inflamatórias: {valorPico} pg/ml - Tempo: {tempoPico} dias")

# Citocinas Anti-Inflamatórias
valorPico = np.max(citocinaAnti)
indicePico = np.argmax(citocinaAnti)
tempoPico = tempo[indicePico]
print(f"Citocinas Anti-Inflamatórias: {valorPico} pg/ml - Tempo: {tempoPico} dias")


# Plotagem 

fig, ax = plt.subplots(1,2, figsize = (12, 5))

# Plota as Células Iba-1+ (micróglias)
ax[0].plot(df['Tempo'], df['Micróglias'], label='Micróglias', linewidth=3, color = 'tab:purple')

# Plota as Células Iba-1+ (micróglias)
ax[0].plot(df['Tempo'], df['Células Iba-1+'], label='Células Iba-1+', linewidth=3, color = 'tab:red')

# Plota os Oligodendrócitos
ax[0].plot(df['Tempo'], df['Oligodendrócitos'], label='Oligodendrócitos', linewidth=3, color = 'tab:green')

# Configurações Visuais
ax[0].set_title('Microglia e Oligodendrócito', fontsize = 11, fontweight='bold')
ax[0].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
ax[0].set_ylabel('Densidade (cells/mm²)', fontsize = 11, fontweight='bold')
ax[0].grid(True) 
ax[0].legend(fontsize = 13) 
ax[0].tick_params(labelsize = 13)

# Plota as Citocinas Pró-Inflamatórias
ax[1].plot(df['Tempo'], df['Citocinas Pró-Inflamatórias'], label='Citocinas Pró-Inflamatórias', linewidth=3, color = 'tab:orange')

ax[1].plot(21, 790, label='Pró', marker = '*', color = 'orange', markersize = 10)
ax[1].plot(21, 1730, label='Anti', marker = '*', color = 'blue', markersize = 10)

# Plota as Citocinas Anti-Inflamatórias
ax[1].plot(df['Tempo'], df['Citocinas Anti-Inflamatórias'], label='Citocinas Anti-Inflamatórias', linewidth=3, color = 'tab:blue')

# Configurações Visuais
ax[1].set_title('Citocinas Pró e Anti-inflamatórias', fontsize = 11, fontweight='bold')
ax[1].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
ax[1].set_ylabel('Concentração (pg/ml)', fontsize = 11, fontweight='bold')
ax[1].grid(True) 
ax[1].legend(fontsize = 13) 
ax[1].tick_params(labelsize = 13)

plt.tight_layout() 
plt.savefig('gráfico.jpg') 
plt.show()