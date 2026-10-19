import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 

arquivo = 'dadosModelo.csv'

# Configurações de fonte
plt.rcParams.update({
    'font.serif': ['Times New Roman'],
})

# Função para plotar os picos de cada função
def printPicos():
    colunas = ['Tempo', 'Micróglia Basal', 'Células Iba-1+', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias', 'T Helper', 'T Cytotoxic', 'T Regulatory', 'Micróglias Totais']
    
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
    microgliaBasal = df_local['Micróglia Basal'].to_numpy()
    celulasIba1 = df_local['Células Iba-1+'].to_numpy()
    oligodendrocitos = df_local['Oligodendrócitos'].to_numpy()
    citocinaPro = df_local['Citocinas Pró-Inflamatórias'].to_numpy()
    citocinaAnti = df_local['Citocinas Anti-Inflamatórias'].to_numpy()
    tHelp = df_local['T Helper'].to_numpy()
    tCytotoxic = df_local['T Cytotoxic'].to_numpy()
    treg = df_local['T Regulatory'].to_numpy()
    microgliasTotais = df_local['Micróglias Totais'].to_numpy()

    # Microglia Basal
    valorPico = np.max(microgliaBasal)
    indicePico = np.argmax(microgliaBasal)
    tempoPico = tempo[indicePico]
    print(f"Microglia Basal: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

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

    # Microglias Totais
    valorPico = np.max(microgliasTotais)
    indicePico = np.argmax(microgliasTotais)
    tempoPico = tempo[indicePico]
    print(f"Microglia Total: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

    # T Helper
    valorPico = np.max(tHelp)
    indicePico = np.argmax(tHelp)
    tempoPico = tempo[indicePico]
    print(f"T Helper: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

    # T Cytotoxic
    valorPico = np.max(tCytotoxic)
    indicePico = np.argmax(tCytotoxic)
    tempoPico = tempo[indicePico]
    print(f"T Cytotoxic: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

    # T Regulatory
    valorPico = np.max(treg)
    indicePico = np.argmax(treg)
    tempoPico = tempo[indicePico]
    print(f"T Regulatory: {valorPico} cells/mm² - Tempo: {tempoPico} dias")

# Função para plotar os marcadores de 21 dias
def plotMarkers(ax):
    ax[2].plot(21, 790, marker = '*', color = 'orange', markersize = 16, label = 'Experimental Data')
    ax[2].plot(21, 1730, marker = '*', color = 'blue', markersize = 16, label = 'Experimental Data')

# Função para plotar os gráficos
def plotModel(arquivo):
    colunas = ['Tempo', 'Micróglia Basal', 'Microglia Ativada', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias', 'T Helper', 'T Cytotoxic', 'T Regulatory', 'Micróglias Totais']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo2: {e}")
        exit()

    fig, ax = plt.subplots(1,3, figsize = (12, 5))

    # Plota a Microglia basal
    ax[0].plot(df_local['Tempo'], df_local['Micróglia Basal'], label='Basal Microglia', linewidth=3, color = 'tab:purple')

    # Plota a Micróglia Ativada
    ax[0].plot(df_local['Tempo'], df_local['Microglia Ativada'], label='Activated Microglia', linewidth=3, color = 'tab:red')

    # Plota os Oligodendrócitos
    ax[0].plot(df_local['Tempo'], df_local['Oligodendrócitos'], label='Oligodendrocyte', linewidth=3, color = 'tab:green')

    # Plota o total de Micróglia
    # ax[0].plot(df_local['Tempo'], df_local['Microglia Total'], label ='Total Microglia', linewidth=3, color = 'tab:brown')

    # Configurações Visuais
    ax[0].set_title('Density of basal microglia, activated microglia,\nand oligodendrocytes', fontsize = 13)
    ax[0].set_xlabel('Time (days)', fontsize = 13)
    ax[0].set_ylabel('Density (cells/mm²)', fontsize = 13)
    ax[0].grid(True) 
    ax[0].legend(fontsize = 10, loc = 'upper right') 
    ax[0].tick_params(labelsize = 12)
    # ax[0].set_ylim(-20, 450)



    # Plota os linfócitos T Helper
    ax[1].plot(df_local['Tempo'], df_local['T Helper'], label='T Helper', linewidth=3, color = 'darkcyan')

    # Plota os linfócitos T Cytotoxic
    ax[1].plot(df_local['Tempo'], df_local['T Cytotoxic'], label='T Cytotoxic', linewidth=3, color = 'crimson')

    # Plota os linfócitos T Cytotoxic
    ax[1].plot(df_local['Tempo'], df_local['T Regulatory'], label='T Regulatory', linewidth=3)

    # Configurações Visuais
    ax[1].set_title('Density of T lymphocytes', fontsize = 13)
    ax[1].set_xlabel('Time (days)', fontsize = 13)
    ax[1].set_ylabel('Density (cells/mm²)', fontsize = 13)
    ax[1].grid(True) 
    ax[1].legend(fontsize = 10, loc = 'upper right') 
    ax[1].tick_params(labelsize = 12)
    # ax[1].set_ylim(-100, 2000)
    plt.tight_layout()
    plt.savefig('modelo.jpg')



    # Plota as Citocinas Pró-Inflamatórias
    ax[2].plot(df_local['Tempo'], df_local['Citocinas Pró-Inflamatórias'], label='Pro-inflammatory Cytokine', linewidth=3, color = 'tab:orange')

    # Plota as Citocinas Anti-Inflamatórias
    ax[2].plot(df_local['Tempo'], df_local['Citocinas Anti-Inflamatórias'], label='Anti-inflammatory Cytokine', linewidth=3, color = 'tab:blue')

    plotMarkers(ax)

    # Configurações Visuais
    ax[2].set_title('Concentration of Pro and Anti-inflammatory Cytokines', fontsize = 13)
    ax[2].set_xlabel('Time (days)', fontsize = 13)
    ax[2].set_ylabel('Concentration (pg/ml)', fontsize = 13)
    ax[2].grid(True) 
    ax[2].legend(fontsize = 10, loc = 'upper right') 
    ax[2].tick_params(labelsize = 12)
    # ax[2].set_ylim(-100, 2000)
    plt.tight_layout()
    plt.savefig('modelo.jpg')

# print("============= PICOS MODELO 2 =============")
# for i in range(1, 10):
#     numNome = i/10
#     arquivo = 'dadosModelo2_epsilon_' + str(i/10) + '.csv'
#     plotModel(arquivo, numNome)

plotModel(arquivo)

plt.show()