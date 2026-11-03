import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 

arquivo = 'dadosModelo1.csv'

# Configurações de fonte
plt.rcParams.update({
    'font.serif': ['Arial'],
})

# Função para plotar o modelo 2
def plotModelEpsilonSweep(arquivo, numNome):
    colunas = ['Tempo', 'Micróglia Basal', 'Microglia Ativada', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias', 'Microglia Total']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo2: {e}")
        exit()

    fig, ax = plt.subplots(1,2, figsize = (16, 8.3))

    # Plota a Microglia basal
    ax[0].plot(df_local['Tempo'], df_local['Micróglia Basal'], label='Basal Microglia', linewidth=5, color = 'tab:purple')

    # Plota a Micróglia Ativada
    ax[0].plot(df_local['Tempo'], df_local['Microglia Ativada'], label='Activated Microglia', linewidth=5, color = 'tab:red')

    # Plota o total de Micróglia
    ax[0].plot(df_local['Tempo'], df_local['Microglia Total'], label ='Total Microglia', linewidth=5, color = 'tab:brown')

    # Plota os Oligodendrócitos
    ax[0].plot(df_local['Tempo'], df_local['Oligodendrócitos'], label='Oligodendrocyte', linewidth=5, color = 'tab:green')

    # Configurações Visuais
    ax[0].set_title('Density of basal microglia, activated microglia,\nand oligodendrocytes', fontsize = 20, fontweight='bold')
    ax[0].set_xlabel('Time (days)', fontsize = 20, fontweight='bold')
    ax[0].set_ylabel('Density (cells/mm²)', fontsize = 20, fontweight='bold')
    ax[0].grid(True) 
    ax[0].legend(fontsize = 20) 
    ax[0].tick_params(labelsize = 20)
    ax[0].set_ylim(-20, 450)


    # plotMarkers(ax)

    # Plota as Citocinas Pró-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Pró-Inflamatórias'], label='Pro-inflammatory Cytokine', linewidth=5, color = 'tab:orange')

    # Plota as Citocinas Anti-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Anti-Inflamatórias'], label='Anti-inflammatory Cytokine', linewidth=5, color = 'tab:blue')

    # Configurações Visuais
    ax[1].set_title('Concentration of Pro and Anti-inflammatory Cytokines', fontsize = 20, fontweight='bold')
    ax[1].set_xlabel('Time (days)', fontsize = 20, fontweight='bold')
    ax[1].set_ylabel('Concentration (pg/ml)', fontsize = 20, fontweight='bold')
    ax[1].grid(True) 
    ax[1].legend(fontsize = 20) 
    ax[1].tick_params(labelsize = 20)
    ax[1].set_ylim(-100, 2000)
    plt.tight_layout() 
    plt.savefig('modelo2_epsilon_'+ str(numNome) +'.jpg')

# Função para plotar os marcadores de 21 dias
def plotMarkers(ax):
    ax[1].plot(21, 790, marker = '*', color = 'orange', markersize = 16, label = 'Dado Experimental')
    ax[1].plot(21, 1730, marker = '*', color = 'blue', markersize = 16, label = 'Dado Experimental')

def plotModel(arquivo):
    colunas = ['Tempo', 'Microglia Homeostatica', 'Microglia Ativada', 'Oligodendrócitos', 'Citocinas Pró-Inflamatórias', 'Citocinas Anti-Inflamatórias', 'Microglia Total']
    
    try:
        df_local = pd.read_csv(arquivo, sep=r',', header=0, names=colunas)
        df_local.columns = colunas
        
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' não encontrado.")
        exit()
    except Exception as e:
        print(f"Erro ao ler o arquivo2: {e}")
        exit()

    fig, ax = plt.subplots(1,2, figsize = (13, 5))

    # Plota a Microglia homeostática
    ax[0].plot(df_local['Tempo'], df_local['Microglia Homeostatica'], label='Micróglia Homeostática', linewidth=3, color = 'tab:purple')

    # Plota a Micróglia Ativada
    ax[0].plot(df_local['Tempo'], df_local['Microglia Ativada'], label='Micróglia Ativada', linewidth=3, color = 'tab:red')

    # Plota o total de Micróglia
    ax[0].plot(df_local['Tempo'], df_local['Microglia Total'], label ='Micróglia Total', linewidth=3, color = 'tab:brown', linestyle = 'dotted')

    # Plota os Oligodendrócitos
    ax[0].plot(df_local['Tempo'], df_local['Oligodendrócitos'], label='Oligodendrócitos', linewidth=3, color = 'tab:green')

    # Configurações Visuais
    ax[0].set_title('Densidade de micróglia homeostática,\nmicróglia ativada, e oligodendrócitos', fontsize = 16, fontweight='bold')
    ax[0].set_xlabel('Tempo (dias)', fontsize = 15, fontweight='bold')
    ax[0].set_ylabel('Densidade (células/mm²)', fontsize = 15, fontweight='bold')
    ax[0].grid(True) 
    ax[0].legend(fontsize = 10, loc = 'center left') 
    ax[0].tick_params(labelsize = 12)
    ax[0].set_ylim(-20, 450)

    # plotMarkers(ax)

    # Plota as Citocinas Pró-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Pró-Inflamatórias'], label='Citocinas Pró-Inflamatórias', linewidth=3, color = 'tab:orange')

    # Plota as Citocinas Anti-Inflamatórias
    ax[1].plot(df_local['Tempo'], df_local['Citocinas Anti-Inflamatórias'], label='Citocinas Anti-Inflamatórias', linewidth=3, color = 'tab:blue')

    # Configurações Visuais
    ax[1].set_title('Concentração de \ncitocinas pró e anti-inflamatórias', fontsize = 16, fontweight='bold')
    ax[1].set_xlabel('Tempo (dias)', fontsize = 15, fontweight='bold')
    ax[1].set_ylabel('Concentração (pg/ml)', fontsize = 15, fontweight='bold')
    ax[1].grid(True) 
    ax[1].legend(fontsize = 10) 
    ax[1].tick_params(labelsize = 12)
    ax[1].set_ylim(-100, 2000)
    plt.tight_layout() 
    plt.savefig('modelo.jpg')

arquivo = 'dadosModelo.csv'
plotModel(arquivo)

plt.show()