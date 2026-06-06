#include <vector>
#include <optional>
#include <limits>
#include "E_BT.h"
#include <iostream>

using namespace std;

ResultadoBT distancias_BT(int n, int m, const vector<vector<int>> &distancias, int max_parejas) {
    
    int nivel = 0;          //El nivel indica en la altura del arbol combinatorio que nos encontramos
    vector<int> s(m, -1);       //Inicializamos el vector con tamaño m, a -1 para indicar que todavia no se han visitado
    int distancia_actual = 0;   //Creamos una variable global para llevar la cuenta de la distancia
    double voa = -1;            //Este es el valor de la distancia máxima que buscamos
    Solucion soa = nullopt;     //Demomento no tenemos solucion, está vacío

    while (nivel != -1) {
        // 1) Genero un hermano en el nivel actual
        //Aquí es donde escogemos a las personas sobre las que vamos a estudiar las distancias
        //que como sabemos, en un árbol combinatorio tienen que ir ordenadas de menor a mayor por eficiencia
        //y evitar repetir y calcular mismos grupos pero distinto orden de personas.
        if(s[nivel] == -1){             //Miramos en el vector, y si está a -1 significa que no ha sido visitado todavía
            if(nivel == 0){             //si nos encontramos en el primer nodo, significa que al ser un árbol combinatorio
                s[nivel] = 0;         //no tenemos restricción todavía para añadir ningún valor así que metemos el primero posible
            }
            else{
                s[nivel] = s[nivel -1] + 1;  //en el caso de que no sea el primer nodo, tenemos que añadir el valor mayor al que esta antes

            }
            //Aquí es donde verdaderamente calculamos las distancias respecto a las personas que hayamos escogido
            //previamente, justo arriba en el if/else.
            int persona_nueva = s[nivel]; //Guardamos el valor de la persona que vamos a estudiar(0,1,2..)  
            /*Y con las personas que hay por delante de él(i<nivel) calculamos la distancia y la vamos metiendo
            a la variable global que creamos al principio.
            Como nos dice que la matriz no es simétrica, tenemos que sumar los 2 valores [i][j] y [j][i]*/  
            for(int i = 0; i < nivel; i++){
                distancia_actual += distancias[s[i]][persona_nueva];    //s[i] es la persona que va antes, si hay 2 pues en una
                distancia_actual += distancias[persona_nueva][s[i]];    //iteracion será la primera y en la segunda iteracion la segunda persona
            }
        /*si llegamos aquí, es porque ya había una persona en el conjunto de personas, entonces para meter otra
        y probar con la otra primero tenemos que restar lo que aportaba esta persona a las distancias como hemos hecho antes
        pero con resta en vez de suma*/
        }else {
            int persona_vieja = s[nivel];
            for(int i = 0; i < nivel; i++){
                distancia_actual -= distancias[s[i]][persona_vieja];
                distancia_actual -= distancias[persona_vieja][s[i]];
            }
            //y probamos con una persona nueva, mayor en este caso de la que había antes y hacemos lo mismo
            //para sumar distancias
            s[nivel] += 1;
            int persona_nueva = s[nivel];
            for(int i = 0; i < nivel; i++){
                distancia_actual += distancias[s[i]][persona_nueva];
                distancia_actual += distancias[persona_nueva][s[i]];
            }
        }

        // 2) Si he encontrado una solución que mejora a voa, la guardo 
        if (nivel == m - 1) {       //si hemos llegado al final
            if (distancia_actual > voa) {   //y la distancia actual es mayor que la óptima(la mayor encontrada hasta el momento)
                voa = distancia_actual;     //guardamos los resultados
                soa = s;
            }
        }

        // 3) Si podríamos llegar a una solución (mejor), seguimos bajando 
        /*en esta parte es donde implementamos la poda. Nuestra finalidad es llegar a calcular el beneficio_estimado,
        que si nos ponemos a pensar, se calcula con las parejas que nos quedan * lo maximo que puedan llegar a sumar esas parejas.
        Recordemos que esto es un caso ficticio, y que se supone siempre el maximo beneficio para hacer la estimación y que no es la
        única poda que se podría hacer.
        Por lo que para llegar a las parejas restantes tenemos que hacer los cálculos previos que se ven reflejados*/

        int parejas_totales = (m*(m-1))/2;  //vemos todas las parejas de personas que se pueden formar
        int nPersonas = nivel + 1; //Porque nivel se empieza a contar en 0 entonces el nº real es +1.
        int parejas_formadas = (nPersonas*(nPersonas - 1)) / 2;       
        int parejas_restantes = parejas_totales - parejas_formadas;
        int beneficio_estimado = parejas_restantes * max_parejas;

        /*Aquí es donde comenzamos a podar, establecemos que si en un supuesto mejor caso se sigue sin superar el valor
        voa, el que nos daría de solución ahora mismo, descartamos directamente, y saltamos al else. En caso de que se 
        cumpla, aumentamos el nivel en 1, es decir, seguimos bajando por esa rama en el árbol y seguimos haciendo cálculos
        porque es posible que se supere al voa*/
        if(nivel < m - 1 && (beneficio_estimado + distancia_actual) > voa){
            nivel++;

        } else {
            // 4) Si no, retrocedo hasta encontrar un nodo con más hermanos
            /*si llegamos al else es que tenemos que retroceder porque por esa rama del árbol no vamos
            a llegar a ninguna solucion que nos interese.
            En el while vemos que mientras que el nivel no sea el primero(nos saldriamos del árbol) y si la persona que tenemos es mayor o igual
            a n-m+nivel, que es un limite puesto para ver cual es la ultima persona que se puede asignar a cada posicion para cumplir que 
            van de menor a mayor y que no se quede nigún hueco vacío, es decir nos aseguramos de que se llene el vector de tamaño m, y no metemos a la
            ultima persona en la primera posicion. Si nuestra persona es mayor o igual que ese limite significa que ya tenemos que retroceder.*/
            while (nivel >= 0 && s[nivel] >= n - m + nivel) {
                for(int i = 0; i < nivel; i++){
                    distancia_actual -= distancias [s[i]][s[nivel]];
                    distancia_actual -= distancias [s[nivel]][s[i]];
                }
                s[nivel] = -1;
                --nivel;
            }
        }
    }
    return {voa, soa};
}