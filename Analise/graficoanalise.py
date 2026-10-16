import numpy as np
import pickle
import matplotlib.pyplot as plt

problem = {
    'num_vars': 13,
    'names': [
        'microglia', 'oligod', 'delta', 'lambda', 'ni', 'p',
        'gamma', 'beta', 'alpha', 'mi', 'kappa', 'citoP', 'citoA'
    ]
}

nomes_saidas = [
    'Micróglia Basal',
    'Micróglia Ativa',
    'Oligodendrócitos',
    'Citocinas Pro',
    'Citocinas Anti',
    'Micróglia Total'
]

with open('sobol_indices.pkl', 'rb') as f:
    Si = pickle.load(f)

fig, axes = plt.subplots(nrows=2, ncols=3, figsize=(18, 10), sharey=True)
axes_flat = axes.flatten()  # deixa a matriz em linhas

x = np.arange(len(problem['names']))
largura = 0.35

for idx, (res, nome_saida) in enumerate(zip(Si, nomes_saidas)):
    ax = axes_flat[idx]
    
    # Extrai os índices S1 e ST
    s1 = res['S1']
    st = res['ST']
    
    # Plota as barras de S1 e ST lado a lado
    ax.bar(x - largura/2, s1, largura, label='$S_1$ (Efeito Direto)', color='#1f77b4')
    ax.bar(x + largura/2, st, largura, label='$S_T$ (Efeito Total)', color='#ff7f0e')
    
    # Configurações de cada subgráfico
    ax.set_title(nome_saida, fontsize=12, fontweight='bold')
    ax.set_xticks(x)
    ax.set_xticklabels(problem['names'], rotation=60, ha='right', fontsize=9)
    ax.grid(axis='y', linestyle='--', alpha=0.5)
    ax.set_ylim(bottom=0)
    
    if idx % 3 == 0:
        ax.set_ylabel('Índice de Sensibilidade', fontsize=11)
    if idx == 0:
        ax.legend(loc='upper right')

plt.suptitle('Análise de Sensibilidade Global de Sobol', fontsize=16, y=1.02)
plt.tight_layout()

# Salva a figura completa em alta resolução
plt.savefig('analise_sobol.png', dpi=300, bbox_inches='tight')
plt.show()