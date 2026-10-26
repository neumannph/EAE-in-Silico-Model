import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

def model (t, y):
    TR, TE = y 

    lambda_E = 1.0e-2
    lambda_R = 100.0
    delta = 1.0 # Antigen presentation 
    ni = 1.0e-2 # Memory
    alpha_E = 1.0 # Maximum Teff proliferation rate
    alpha_R = 0.25 # Maximum Treg proliferation and activation rate
    gamma_E = 2.0e-1 # Teff death, anergy and migration Rate
    gamma_R = 2.0e-1 # Treg death, anergy and migration Rate
    kappa_E = 1000.0 # Teff cell population sizes leading to half maximal effect counterpart
    kappa_R = 200.0 # Treg cell population sizes leading to half maximal effect
    h = 5 # Hill coefficient

    dTE_dt = (lambda_E * delta) - (TE * ni) + ((TE * alpha_E * kappa_R**h) / (kappa_R**h + TR**h)) - ((TE * gamma_E * TR**h) / (kappa_R**h + TR**h))
    dTR_dt = (lambda_R * delta) - (TR * ni) + ((TR * alpha_R * TE**h) / (kappa_E**h + TE**h)) - (TR * gamma_R)

    return [dTE_dt, dTR_dt]

y0 = [1000.0, 200.0]  # Initial conditions for TR and TE
t_span = (0, 100)  # Time span for the simulation

t_eval = np.linspace(t_span[0], t_span[1], 1000)

solucao = solve_ivp(model, t_span, y0, t_eval=t_eval)

# 4. Plotar os resultados
plt.figure(figsize=(10, 5))
plt.plot(solucao.t, solucao.y[0], label='EFFECTOR T CELLS', color='red')
plt.plot(solucao.t, solucao.y[1], label='REGULATORY T CELLS', color='blue')

plt.title('População de Células T Efetoras e Reguladoras ao Longo do Tempo')
plt.xlabel('Tempo')
plt.ylabel('População')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()