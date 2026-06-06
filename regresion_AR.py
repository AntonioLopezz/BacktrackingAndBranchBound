import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Leer CSV
df = pd.read_csv('figurasAR/resultados_AR.csv')

# Calcular variables auxiliares
df['n'] = df['Longitud']
df['n2'] = df['Longitud'] ** 2

# --- Generar figura sin regresion ---

plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso con escala logarítmica')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/puntos_peor_log_AR.pdf')

# idem pero sin log

plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/puntos_peor_AR.pdf')

# --- REGRESIÓN PARA PEOR CASO: T(n) vs n² ---
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['n2'], df['PeorCaso'])

# Resultados
lineas = [
    f"  Regresión lineal PeorCaso ~ n²",
    f"  Pendiente: {slope_peor:.6f}",
    f"  R²: {r_peor**2:.4f}",
    f"  MSE: {np.mean((df['PeorCaso'] - (slope_peor * df['n2'] + intercept_peor))**2):.4f}",
    f"  p-valor: {p_peor:.4e}",
]
for l in lineas:
    print(l)
with open('figurasAR/regresion_AR.txt', 'w') as f:
    f.write('\n'.join(lineas) + '\n')

# Ajuste peor caso ~ Θ(n²)
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n2'] + intercept_peor, label=r'Ajuste $\Theta(n^2)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso $\sim \Theta(n^2)$')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/ajuste_peor_log_AR.pdf')

# idem pero sin log

plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n2'] + intercept_peor, label=r'Ajuste $\Theta(n^2)$')
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso $\sim \Theta(n^2)$')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/ajuste_peor_AR.pdf')