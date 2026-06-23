import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 

arquivo = 'dadosModelo1.csv'

# Configurações de fonte
plt.rcParams.update({
    'font.family': 'serif', 
    'font.serif': ['Times New Roman'],
})

def printPicosModel1():
    
    colunas = ['Tempo', 'Micróglias', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo1: {e}")
        exit()


    tempo = df_local['Tempo'].to_numpy()
    microglias = df_local['Micróglias'].to_numpy()
    oligodendrocitos = df_local['Oligodendrócitos'].to_numpy()
    citocinaPro = df_local['Citocinas Pró-Inflamatórias'].to_numpy()
    citocinaAnti = df_local['Citocinas Anti-Inflamatórias'].to_numpy()

    # Microglias
    valorPico = np.max(microglias)
    indicePico = np.argmax(microglias)
    tempoPico = tempo[indicePico]
    print(f"Microglias: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

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

def printPicosModel2():
    colunas = ['Tempo', 'Micróglias', 'Células Iba-1+', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo2: {e}")
        exit()


    tempo = df_local['Tempo'].to_numpy()
    microglias = df_local['Micróglias'].to_numpy()
    celulasIba1 = df_local['Células Iba-1+'].to_numpy()
    oligodendrocitos = df_local['Oligodendrócitos'].to_numpy()
    citocinaPro = df_local['Citocinas Pró-Inflamatórias'].to_numpy()
    citocinaAnti = df_local['Citocinas Anti-Inflamatórias'].to_numpy()

    # Microglias
    valorPico = np.max(microglias)
    indicePico = np.argmax(microglias)
    tempoPico = tempo[indicePico]
    print(f"Microglias: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

    # Células Iba-1+
    valorPico = np.max(celulasIba1)
    indicePico = np.argmax(celulasIba1)
    tempoPico = tempo[indicePico]
    print(f"Células Iba-1+: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

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

# Função para plotar o modelo de 21 dias
def plotModel1(arquivo):
    colunas = ['Tempo', 'Micróglias', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo1: {e}")
        exit()

    fig, ax = plt.subplots(1,2, figsize = (12, 5))

    plotMarkers21Days(ax)

    # Plota as Células Iba-1+ (Micróglias)
    ax[0].plot(df_local['Tempo'], df_local['Micróglias'], label='Micróglias', linewidth=3, color = 'tab:red')

    # Plota os Oligodendrócitos
    ax[0].plot(df_local['Tempo'], df_local['Oligodendrócitos'], label='Oligodendrócitos', linewidth=3, color = 'tab:green')

    # Configurações Visuais
    ax[0].set_title('Densidade de microglia basal, microglia ativada e oligodendrócito\n (sem tratamento)', fontsize = 12, fontweight='bold')
    ax[0].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
    ax[0].set_ylabel('Densidade (cells/mm²)', fontsize = 11, fontweight='bold')
    ax[0].grid(True) 
    ax[0].legend(fontsize = 13) 
    ax[0].tick_params(labelsize = 13)

    # Plota as Citocinas Pró-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Pró-Inflamatórias'], label='Citocinas Pró-Inflamatórias', linewidth=3, color = 'tab:orange')

    # Plota as Citocinas Anti-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Anti-Inflamatórias'], label='Citocinas Anti-Inflamatórias', linewidth=3, color = 'tab:blue')

    # Configurações Visuais
    ax[1].set_title('Concentração de Citocinas Pró e Anti-inflamatórias', fontsize = 12, fontweight='bold')
    ax[1].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
    ax[1].set_ylabel('Concentração (pg/ml)', fontsize = 11, fontweight='bold')
    ax[1].grid(True) 
    ax[1].legend(fontsize = 13) 
    ax[1].tick_params(labelsize = 13)
    plt.tight_layout() 
    plt.ylim(0, 2000)
    plt.savefig('modelo_21_dias.jpg') 

# Função para plotar os marcadores de 21 dias
def plotMarkers21Days(ax):
    ax[1].plot(21, 790, marker = '*', color = 'orange', markersize = 10)
    ax[1].plot(21, 1730, marker = '*', color = 'blue', markersize = 10)

# Função para plotar o modelo de 58 dias
def plotModel2(arquivo):
    colunas = ['Tempo', 'Micróglias Basal', 'Células Iba-1+', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo2: {e}")
        exit()

    fig, ax = plt.subplots(1,2, figsize = (12, 5))

    # Plota as Células Iba-1+ (Micróglias Basal)
    ax[0].plot(df_local['Tempo'], df_local['Micróglias Basal'], label='Micróglia Basal', linewidth=3, color = 'tab:purple')

    # Plota as Células Iba-1+ (Micróglias Ativadas)
    ax[0].plot(df_local['Tempo'], df_local['Células Iba-1+'], label='Células Iba-1+', linewidth=3, color = 'tab:red')

    # Plota os Oligodendrócitos
    ax[0].plot(df_local['Tempo'], df_local['Oligodendrócitos'], label='Oligodendrócitos', linewidth=3, color = 'tab:green')

    # Configurações Visuais
    ax[0].set_title('Densidade de microglia basal, microglia ativada e oligodendrócito\n(sem tratamento)', fontsize = 12, fontweight='bold')
    ax[0].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
    ax[0].set_ylabel('Densidade (cells/mm²)', fontsize = 11, fontweight='bold')
    ax[0].grid(True) 
    ax[0].legend(fontsize = 13) 
    ax[0].tick_params(labelsize = 13)

    plotMarkers21Days(ax)

    # Plota as Citocinas Pró-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Pró-Inflamatórias'], label='Citocinas Pró-Inflamatórias', linewidth=3, color = 'tab:orange')

    # Plota as Citocinas Anti-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Anti-Inflamatórias'], label='Citocinas Anti-Inflamatórias', linewidth=3, color = 'tab:blue')

    # Configurações Visuais
    ax[1].set_title('Concentração de Citocinas Pró e Anti-inflamatórias\n(MOG 100μg)', fontsize = 12, fontweight='bold')
    ax[1].set_xlabel('Tempo (dias)', fontsize = 11, fontweight='bold')
    ax[1].set_ylabel('Concentração (pg/ml)', fontsize = 11, fontweight='bold')
    ax[1].grid(True) 
    ax[1].legend(fontsize = 13) 
    ax[1].tick_params(labelsize = 13)
    plt.tight_layout() 
    plt.ylim(0, 2000)
    plt.savefig('modelo_58_dias.jpg')


# Função para plotar os marcadores de 58 dias MOG 100ug
""" def plotMarkers58Days(ax):
    ax[1].plot(7, 394, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(10, 208, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(14, 44, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(21, 159, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(58, 292, marker = '*', color = 'blue', markersize = 10)
 """
# Função para plotar os marcadores de 58 dias MOG 300ug
""" def plotMarkers58Days(ax):
    ax[1].plot(7, 249, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(10, 126, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(14, 375, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(21, 161, marker = '*', color = 'blue', markersize = 10)
    ax[1].plot(58, 192, marker = '*', color = 'blue', markersize = 10)
 """

#print("============= PICOS MODELO 1 =============")
#printPicosModel1(arquivo)
#plotModel1(arquivo)

print("============= PICOS MODELO 2 =============")
arquivo = 'dadosModelo2.csv'
printPicosModel2()
plotModel2(arquivo)

plt.show()