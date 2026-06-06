#include <iostream>
#include <cassert>
#include "E_AR.h"

//solo un mecanico puede reparar una averia
void testCaso1Enunciado() {
    int M = 2, A = 3;
    vector<vector<int>> C = {
        {0, 1, 0},
        {0, 0, 0}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 1);
}

//caso 2 - todos los mecanicos pueden reparar alguna averia
void testCaso2Enunciado() {
    int M = 4, A = 3;
    vector<vector<int>> C = {
        {1, 0, 1},
        {1, 1, 0},
        {0, 0, 0},
        {1, 1, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 3);
}

//caso 3 - hay una averia que no se puede reparar, otra que solo la puede hacer 1 por lo que esa averia la tiene que tener
//el mecanico que la tiene y la otra como la tienen los  2 pues el que falta, por lo que de resultado.first == 2
void testCaso3Enunciado() {
    int M = 2, A = 3;
    vector<vector<int>> C = {
        {0, 0, 1},
        {1, 0, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 2);
}

//Ningun mecanico puede reparar ninguna averia
void testNadiePuedeNada() {
    int M = 3, A = 3;
    vector<vector<int>> C = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 0);
}

//Todos pueden reparar todas las averias
void testTodosPuedenTodo() {
    int M = 3, A = 3;
    vector<vector<int>> C = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 3);
}

//Mas averias que mecanicos, solo se pueden reparar M averias como maximo, el numero de mecanicos
void testMasAveriaQuesMecanicos() {
    int M = 2, A = 4;
    vector<vector<int>> C = {
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 2);
}

//Mas mecanicos que averias, se reparan todas las averias
void testMasMecanicoQueAverias() {
    int M = 4, A = 2;
    vector<vector<int>> C = {
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 2);
}

//Cada mecanico solo puede reparar una averia concreta
void testEspecializacionTotal() {
    int M = 3, A = 3;
    vector<vector<int>> C = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 3);
}

//Un unico mecanico puede repararlo todo. Solo se reparara una averia pues un mecanico solo puede tener una averia
void testUnSoloMecanico() {
    int M = 1, A = 3;
    vector<vector<int>> C = {
        {1, 1, 1}
    };
    auto resultado = Asignacion_AR(M, A, C);
    assert(resultado.first == 1);
}

int main() {
    testCaso1Enunciado();
    testCaso2Enunciado();
    testCaso3Enunciado();
    testNadiePuedeNada();
    testTodosPuedenTodo();
    testMasAveriaQuesMecanicos();
    testMasMecanicoQueAverias();
    testEspecializacionTotal();
    testUnSoloMecanico();
    std::cout << "Todos los tests pasaron!" << std::endl;
    return 0;
}