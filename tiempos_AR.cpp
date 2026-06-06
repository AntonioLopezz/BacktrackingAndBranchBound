#include <iostream>
#include "E_AR.h"
#include <cassert>
#include <math.h>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

// Peor caso: solo el ultimo mecanico puede reparar todas las averias.
// El bucle interior siempre recorre todos los mecanicos hasta llegar al ultimo.
tuple<int,int,vector<vector<int>>> generarPeorCaso(int n) {
    int M = n;
    int A = n;

    vector<vector<int>> C(M, vector<int>(A, 0));

    for(int j = 0; j < A; j++)
        C[M-1][j] = 1;

    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 1);

    return {M, A, C};
}

double medirTiempo(tuple<int,int,vector<vector<int>>> caso) {
    auto start = std::chrono::high_resolution_clock::now();

    auto M = get<0>(caso);
    auto A = get<1>(caso);
    auto C = get<2>(caso);

    auto resultado = Asignacion_AR(M, A, C);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion = end - start;
    return duracion.count();
}

double mediana(std::vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;

    std::sort(v.begin(), v.end());

    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    std::vector<int> longitudes;
    for (int i = 0; i <= 6; i += 1) {
        longitudes.push_back(100 * pow(2, i));  // 100, 200, 400, ..., 6400
    }

    std::ofstream csv("figurasAR/resultados_AR.csv");
    csv << "Longitud,PeorCaso\n";

    cout << "Calculando tiempos (M = A = n)..." << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int n : longitudes) {
        auto peorCaso = generarPeorCaso(n);
        vector<double> peoresCasos;
        for (int j = 0; j < 10; j += 1) {
            auto peorTiempo = medirTiempo(peorCaso);
            peoresCasos.push_back(peorTiempo);
        }
        auto medianaPeorTiempo = mediana(peoresCasos);

        csv << n << "," << medianaPeorTiempo << "\n";
        cout << "n=" << n << " | PeorCaso: " << medianaPeorTiempo << " ms" << endl;
    }

    csv.close();
    cout << "-------------------------------------------------------------" << endl;
    cout << "Se ha creado figurasAR/resultados_AR.csv" << endl;
    return 0;
}
