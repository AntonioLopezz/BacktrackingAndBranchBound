#include <iostream>
#include <vector>
#include <cassert>
#include "E_BT.h"

using namespace std;

void testEmpateTotal() {
    int n = 4;
    int m = 2;

    vector<vector<int>> distancias = {
        {0, 10, 10, 10},
        {10, 0, 10, 10},
        {10, 10, 0, 10},
        {10, 10, 10, 0}
    };

    int max_parejas = 20;       //Este va a ser nuestro voa
    auto resultado = distancias_BT(n, m, distancias, max_parejas);
    assert(resultado.voa == 20);
}

void testMejorAlFinal() {
    int n = 4, m = 2;
    vector<vector<int>> distancias = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 50},
        {1, 1, 50, 0}
    };
    int max_parejas = 100;
    auto resultado = distancias_BT(n, m, distancias, max_parejas);
    assert(resultado.voa == 100);
}

void testTodosObligatorios() {
    int n = 3, m = 3; //como m == n tenemos que mirar todos los elementos
    vector<vector<int>> distancias = {
        {0, 5, 2},
        {5, 0, 3},
        {2, 3, 0}
    };
    //(0,1)=10, (0,2)=4, (1,2)=6. Total = 20
    int max_parejas = 10;
    auto resultado = distancias_BT(n, m, distancias, max_parejas);
    assert(resultado.voa == 20); 
}

void testDistanciasCero() {
    int n = 4, m = 3;
    vector<vector<int>> distancias(n, vector<int>(n, 0));  //dejamos toda la matriz a 0
    int max_parejas = 0;
    auto resultado = distancias_BT(n, m, distancias, max_parejas);
    assert(resultado.voa == 0); 
}

void testMejorCaso() { //Ponemos el caso que mas suma al principio para establecer un voa alto y podar el resto, muy rapido
    int n = 5;
    int m = 3;

    vector<vector<int>> distancias = {
        { 0, 10, 10,  1,  1}, 
        {10,  0, 10,  1,  1}, 
        {10, 10,  0,  1,  1}, 
        { 1,  1,  1,  0,  1}, 
        { 1,  1,  1,  1,  0}  
    };

    // La mejor pareja posible suma 10 de ida + 10 de vuelta = 20 puntos.
    int max_parejas = 20;

    auto resultado = distancias_BT(n, m, distancias, max_parejas);

    // Cada uno da 20 puntos. Total = 60 puntos.
    assert(resultado.voa == 60);
}

int main() {
    testEmpateTotal();
    testMejorAlFinal();
    testTodosObligatorios();
    testDistanciasCero();
    testMejorCaso();
    
    cout << "Todos los tests unitarios de backtracking pasaron correctamente" << endl;
    return 0;
}