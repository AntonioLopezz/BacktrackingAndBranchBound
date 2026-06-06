#include <iostream>
#include <vector>
#include <algorithm>
#include "E_AR.h"

//Funcion que usamos para comparar averias y luego pasarlas al sort
bool compararAverias(const Averia& a, const Averia& b){
        return a.numMecanicos < b.numMecanicos;
    }


/*La funcion que tenemos nos devuelve un entero para ver el numero de averias reparadas y un vector de enteros
diciendo qué mecanico se asigno a cada averia. Donde M son el numero de mecanicos, A el numero de averias, y el vector
de vectores de enteros representa una matriz de M lineas en el que cada una indica si el mecanico puede reparar la averia o no
*/
pair<int,vector<int>> Asignacion_AR(int M, int A, const vector<vector<int>>& C){
    
    //Inicializacion
    vector<int> asignacion(A,0);    //Creamos un vector de tamaño A(nº de averias) inicializado a 0(ningun mecanico asignado)
     int averiasReparadas = 0;      //Contador inicialmente a 0
    vector<bool> mecanicoOcupado(M,false);      //Creamos un vector tamaño M(mecanicos) en los que todos estan libres

    //Para cada averia j, las columnas de nuestra matriz, necesitamos contar cuantos mecanicos la pueden reparar(valores a 1)
    /*Calculamos cuantos mecanicos pueden reparar cada averia para poder ordenar, pero necesitamos un vector
    de tipo averia ya que si ordenaramos directamente perderiamos el indice de la averia, es decir tendriamos el vector
    ordenado indicando el numero de mecanicos disponible pero no sabriamos a que averia correspoderia
    */
    vector<Averia>averias(A);          //Creamos un vector de tipo averia(indice,nMecanicos) para guardar cada averia con su nº de mecanicos
    for(int j = 0; j < A; j++){
        int cont = 0;
        averias[j].indice = j;
        for(int i = 0; i < M; i++){
            if(C[i][j] == 1){
                cont++;
            }
        }
        averias[j].numMecanicos = cont;
    }    

    //Vamos ahora a comparar las averias, nos interesa tener primero la que menos mecanicos puedan hacerla ya que son mas "exclusivas"

    sort(averias.begin(), averias.end(),compararAverias);

    /*Ahora recorremos todas las averías, las mas dificiles primero(menos mecanicos) y para cada una de estas, recorrer los mecanicos
    y ver que pueda reparar esta averia y que esta libre y asignarsela. Marcamos como ocupado al mecanico y como resuelta la averia
    */
    for(int j = 0; j < A; j++){
        int averia = averias[j].indice;     //Accedemos a cada una de las averias con su numero de mecanicos

        for(int i = 0; i < M; i++){         //Recorremos todos los mecanicos
            if(C[i][averia] == 1 && mecanicoOcupado[i] == false){  //Si el mecanico puede reparar la averia y está libre(al principio todos estan libres)
                asignacion[averia] =i + 1;                  //Le asignamos la averia al mecanico, i + 1 porque los mecanicos empiezan en 1
                mecanicoOcupado[i] = true;              //Marcamos el mecanico como ocupado
                averiasReparadas++;                     //Sumamos al contador global
                break;
            }
        }
    }
    return make_pair(averiasReparadas,asignacion);
}