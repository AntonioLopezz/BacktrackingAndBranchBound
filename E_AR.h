#include <vector>

using namespace std;

struct Averia {
    int indice;
    int numMecanicos;   //nº de mecanicos que pueden hacerla
};
bool compararAverias(const Averia& a, const Averia& b);

pair<int,vector<int>> Asignacion_AR(int M, int A, 
                                 const vector<vector<int>>& C); 
                                 