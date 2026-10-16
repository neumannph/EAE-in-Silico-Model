import numpy as np
import matplotlib.pyplot as plt

nomes_parametros = [
    'microglia', 'oligod', 'delta', 'lambda', 'ni', 'p',
    'gamma', 'beta', 'alpha', 'mi', 'kappa', 'citoP', 'citoA'
]

nomes_saidas = [
    'Micróglia Basal',
    'Micróglia Ativa',
    'Oligodendrócitos',
    'Citocinas Pro',
    'Citocinas Anti',
    'Micróglia Total'
]

param_values = np.load('param_values.npy')
Y = np.load('resultados_Y.npy')

id_saida = 5
id_param = 12

nome_saida_sel = nomes_saidas[id_saida]
nome_param_sel = nomes_parametros[id_param]

x_valores = param_values[:, id_param]
y_valores = Y[:, id_saida]

num_bins = 20
bins = np.linspace(x_valores.min(), x_valores.max(), num_bins + 1) #A 1ª caixa guarda só os brinquedos com pouca microglia.   A 20ª caixa guarda os brinquedos com muita microglia
bin_centers = (bins[:-1] + bins[1:]) / 2

medias = [] #Uma para anotar o tamanho médio dos brinquedos de cada caixa.
limite_inf = [] # Uma para anotar o brinquedo mais baixo daquela caixa.
limite_sup = [] # Uma para anotar o brinquedo mais alto daquela caixa

for i in range(num_bins):
    indices = (x_valores >= bins[i]) & (x_valores < bins[i+1])
    dados_faixa = y_valores[indices]
    
    if len(dados_faixa) > 0:
        medias.append(np.mean(dados_faixa))
        limite_inf.append(np.percentile(dados_faixa,5))
        limite_sup.append(np.percentile(dados_faixa,95))
    else:
        medias.append(np.nan)
        limite_inf.append(np.nan)
        limite_sup.append(np.nan)

medias = np.array(medias)
limite_inf = np.array(limite_inf)
limite_sup = np.array(limite_sup)

plt.figure(figsize=(8, 5))

plt.fill_between(
    bin_centers, limite_inf, limite_sup, 
    color='gray', alpha=0.35, label='Intervalo de Variação'
)

plt.plot(bin_centers, medias, color='black', linewidth=2, label='Média')

plt.title(f'{nome_saida_sel} vs {nome_param_sel}', fontsize=12, fontweight='bold')
plt.xlabel(f'Parâmetro: {nome_param_sel}', fontsize=11)
plt.ylabel(f'{nome_saida_sel}', fontsize=11)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(loc='best')

plt.tight_layout()

nome_arquivo = f'linha_media_{nome_saida_sel.lower().replace(" ", "_")}_{nome_param_sel}.png'
plt.savefig(nome_arquivo, dpi=300, bbox_inches='tight')
plt.show()