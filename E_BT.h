#include <vector>
#include <optional>

using namespace std;

using Solucion = optional<vector<int>>;

struct ResultadoBT {
    double voa;
    Solucion soa;
};

ResultadoBT distancias_BT(int n,int m, const vector<vector<int>> &distancias,int max_parejas);