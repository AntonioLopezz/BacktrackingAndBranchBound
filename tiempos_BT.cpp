#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <tuple>
#include "E_BT.h"
#include <random>

using namespace std;

// =================================================================
// PEOR CASO: Todas las distancias son iguales. 
// La poda apenas hace efecto porque siempre cree que puede empatar.
// =================================================================
tuple<int, int, vector<vector<int>>, int> generarPeorCaso(int n, int semilla = 42) {
    int m = n / 2;
    mt19937 gen(semilla); // Semilla fija para reproducibilidad
    uniform_int_distribution<> dist(1, 10);
    
    vector<vector<int>> distancias(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(i != j) distancias[i][j] = dist(gen);
    
    int max_parejas = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            max_parejas = max(max_parejas, distancias[i][j] + distancias[j][i]);
    
    return {n, m, distancias, max_parejas};
}

// =================================================================
// MEJOR CASO: La mejor pareja está al principio del todo.
// La poda actúa de inmediato y descarta el resto del árbol.
// =================================================================
tuple<int, int, vector<vector<int>>, int> generarMejorCaso(int n) {
    int m = n / 2; 
    
    vector<vector<int>> distancias(n, vector<int>(n, 0)); // Matriz a 0
    
    // Solo los primeros 'm' invitados tienen una puntuación bestial
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i != j) distancias[i][j] = 50; 
        }
    }
    
    int max_parejas = 100; // 50 ida + 50 vuelta
    return {n, m, distancias, max_parejas};
}

// =================================================================
// FUNCIONES PARA MEDIR TIEMPOS Y CALCULAR MEDIANAS
// =================================================================
double medirTiempo(tuple<int, int, vector<vector<int>>, int> caso) {
    auto start = chrono::high_resolution_clock::now();

    auto n = get<0>(caso);
    auto m = get<1>(caso);
    auto distancias = get<2>(caso);
    auto max_parejas = get<3>(caso);

    // Llamamos a tu algoritmo
    distancias_BT(n, m, distancias, max_parejas);  

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = end - start;
    
    return duracion.count(); // Devuelve el tiempo en milisegundos
}

double mediana(vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;
    sort(v.begin(), v.end());
    if (n % 2 == 1) return v[n / 2];
    else return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

// =================================================================
// MAIN PRINCIPAL
// =================================================================
int main() {
    vector<int> longitudes;
    
    for (int i = 4; i <= 22; i += 2) { 
        longitudes.push_back(i);
    }
    
    // Creamos el archivo CSV
    ofstream csv("figurasBT/resultados_BT.csv");
    csv << "N,Tiempo_PeorCaso_ms,Tiempo_MejorCaso_ms\n";

    cout << "Calculando tiempos (esto puede tardar un poco en N grandes)..." << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int n : longitudes) {
        auto peorCaso = generarPeorCaso(n);
        auto mejorCaso = generarMejorCaso(n);

        // --- Medir el Peor Caso ---
        vector<double> tiempos_peor;
        for (int j = 0; j < 5; j++) {
            tiempos_peor.push_back(medirTiempo(peorCaso));
        }
        double mediana_peor = mediana(tiempos_peor);

        // --- Medir el Mejor Caso ---
        vector<double> tiempos_mejor;
        for (int j = 0; j < 5; j++) {
            tiempos_mejor.push_back(medirTiempo(mejorCaso));
        }
        double mediana_mejor = mediana(tiempos_mejor);

        // Guardar resultados en el CSV
        csv << n << "," << mediana_peor << "," << mediana_mejor << "\n";
        
        // Imprimir por pantalla para ver que el programa no se ha colgado
        cout << "N=" << n << " (m=" << n/2 << ") | Peor: " << mediana_peor << " ms | Mejor: " << mediana_mejor << " ms" << endl;
    }

    csv.close();
    cout << "-------------------------------------------------------------" << endl;
    cout << "Se ha creado el archivo resultados_BT.csv" << endl;
    
    return 0;
}