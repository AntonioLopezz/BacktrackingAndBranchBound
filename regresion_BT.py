import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# 1. Leer nuestro CSV
df = pd.read_csv('figurasBT/resultados_BT.csv')

# 2. Calcular variables auxiliares para linealizar las curvas
df['n'] = df['N']
df['2^n'] = np.power(2, df['N']) # Transformación para el Peor Caso (Exponencial)

# --- REGRESIÓN PARA EL PEOR CASO: T(n) vs 2^n ---
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['2^n'], df['Tiempo_PeorCaso_ms'])

# --- REGRESIÓN PARA EL MEJOR CASO: T(n) vs n ---
slope_mejor, intercept_mejor, r_mejor, p_mejor, _ = stats.linregress(df['n'], df['Tiempo_MejorCaso_ms'])

# ==========================================
# IMPRIMIR RESULTADOS EN CONSOLA (Para copiar a la memoria)
# ==========================================
lineas = [
    f"  Regresión lineal PeorCaso ~ 2^N",
    f"  Pendiente: {slope_peor:.6e}",
    f"  R²: {r_peor**2:.4f}",
    f"  MSE: {np.mean((df['Tiempo_PeorCaso_ms'] - (slope_peor * df['2^n'] + intercept_peor))**2):.4f}",
    f"  p-valor: {p_peor:.4e}",
    f"",
    f"  Regresión lineal MejorCaso ~ N",
    f"  Pendiente: {slope_mejor:.6f}",
    f"  R²: {r_mejor**2:.4f}",
    f"  MSE: {np.mean((df['Tiempo_MejorCaso_ms'] - (slope_mejor * df['n'] + intercept_mejor))**2):.4f}",
    f"  p-valor: {p_mejor:.4e}",
]
for l in lineas:
    print(l)
with open('figurasBT/regresion_BT.txt', 'w') as f:
    f.write('\n'.join(lineas) + '\n')

# ==========================================
# GENERAR GRÁFICAS PARA EL PDF
# ==========================================

# Gráfica 1: Comparativa de Peor vs Mejor (Puntos reales)
plt.figure(figsize=(8, 6))
plt.scatter(df['N'], df['Tiempo_PeorCaso_ms'], label='Peor Caso (La poda no actúa)', marker='x', color='red')
plt.scatter(df['N'], df['Tiempo_MejorCaso_ms'], label='Mejor Caso (La poda corta rápido)', marker='o', color='green')
plt.xlabel('Número de Personas (N)')
plt.ylabel('Tiempo (ms)')
plt.title('Comparativa de Tiempos: Efecto de la Poda en Backtracking')
plt.legend()
plt.grid(True)
plt.savefig('figurasBT/comparativa_poda_BT.pdf')

# Gráfica 2: Ajuste Teórico del Peor Caso
plt.figure(figsize=(8, 6))
plt.plot(df['N'], df['Tiempo_PeorCaso_ms'], 'x', color='red', label='Tiempos Reales Peor Caso')
plt.plot(df['N'], slope_peor * df['2^n'] + intercept_peor, '--', color='blue', label=r'Ajuste Teórico $\Theta(2^N)$')
plt.xlabel('Número de Personas (N)')
plt.ylabel('Tiempo (ms)')
plt.title(r'Contraste Teórico-Experimental Peor Caso $\sim \Theta(2^N)$')
plt.legend()
plt.grid(True)
plt.savefig('figurasBT/ajuste_peor_caso_BT.pdf')

# Gráfica 3: Ajuste Teórico del Mejor Caso
plt.figure(figsize=(8, 6))
plt.plot(df['N'], df['Tiempo_MejorCaso_ms'], 'o', color='green', label='Tiempos Reales Mejor Caso')
plt.plot(df['N'], slope_mejor * df['n'] + intercept_mejor, '--', color='orange', label=r'Ajuste Teórico $\Theta(N)$')
plt.xlabel('Número de Personas (N)')
plt.ylabel('Tiempo (ms)')
plt.title(r'Contraste Teórico-Experimental Mejor Caso $\sim \Theta(N)$')
plt.legend()
plt.grid(True)
plt.savefig('figurasBT/ajuste_mejor_caso_BT.pdf')

print("Se han generado 3 archivos PDF con las gráficas")