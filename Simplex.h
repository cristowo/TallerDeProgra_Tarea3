#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
Esta clase resuelve el problema de optimizacion
lineal con variables reales [x1,....,xn]. 
*/
class Simplex {
public:
    std::vector<std::vector<float>> a;
    int m1; // numero de restricciones <=
    int m2; // ... >=
    int m3; // igualdad
    int N; // cantidad de variables
    int M; // cantidad de restricciones
    int NP; // cantidad de variable no basicas
    int MP; // cantidad de variables basicas
    bool solved; // si es que esta resuelto
    vector<int> izrov;
    vector <int> iposv;
    Simplex(int m1, int m2, int m3);
    ~Simplex();
    void solve(); // resuelve el simplex
    bool loadTxt(string filename); // carga la matriz de filename
    Simplex *clone(); // copiar el simplex
    void insertConstraint(int b, int var, int type);
    void print(); // imprime la matriz
    private:
    int NM1M2;
    void simplx(int m, int n, int m1, int m2, int m3, int *icase);
    void simp1(int mm, vector<int> ll, int nll, int iabf, int *kp, float *bmax); 
    void simp2(int m, int n, int *ip, int kp); 
    void simp3(int i1, int k1, int ip, int kp); 
};