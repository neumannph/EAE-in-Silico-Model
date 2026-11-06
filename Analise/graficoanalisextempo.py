import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Carregando séries temporais...")
df_tempo = pd.read_csv('serie_temporal_completa.csv')

# Limpa eventuais espaços nos nomes das colunas
df_tempo.columns = df_tempo.columns.str.strip()

# Tuplas estruturadas como: (Nome exato no CSV, Nome formatado para exibição)
variaveis = [
    ('Micróglia_Homeostatica', 'Micróglia Homeostática'),
    ('Micróglia_Ativa', 'Micróglia Ativa'),
    ('Oligodendrócitos', 'Oligodendrócitos'),
    ('Citocina_Pro', 'Citocina Pro-inflamatória'),
    ('Citocina_Anti', 'Citocina Anti-inflamatória'),
    ('Micróglia_Total', 'Micróglia Total')
]

plt.rcParams['font.size'] = 10
plt.rcParams['figure.autolayout'] = True

fig, axes = plt.subplots(3, 2, figsize=(12, 10))
axes = axes.flatten()

grupo_tempo = df_tempo.groupby('tempo_t')

for idx, (col_csv, nome_display) in enumerate(variaveis):
    if col_csv not in df_tempo.columns:
        print(f"Erro: Coluna '{col_csv}' não encontrada no CSV.")
        continue
        
    media = grupo_tempo[col_csv].mean()
    std = grupo_tempo[col_csv].std()
    tempo = media.index

    ax = axes[idx]
    ax.plot(tempo, media, color='tab:blue', linewidth=2, label='Média')
    ax.fill_between(tempo, media - std, media + std, color='tab:blue', alpha=0.2, label='±1 Desvio Padrão')
    
    ax.set_title(f'{nome_display}')
    ax.set_xlabel('Tempo (t)')
    ax.grid(True, linestyle='--', alpha=0.6)
    ax.legend(loc='upper right')

plt.show()