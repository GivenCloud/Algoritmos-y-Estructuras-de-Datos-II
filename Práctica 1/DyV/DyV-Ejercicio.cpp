#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

string C = "abcdeafabcdeeabcdeeffabcbcdefabcdeeabfabcdeeabcdeeffabccdeeffabcfabcdeeabcdeefffabcdeeabcdeeffabcabcde";

bool Pequeño(int p, int q) {    //Compruebo si la subcadena es de tamaño 5 o menos
    return (q-p+1 <= 5);
}

int Dividir(int p, int q) {     //Calculo cual sería la mitad de la cadena
    return (p+q) / 2;
}

bool esCadenaValida(int p, int q) {     //Con esta función extraigo los 5 caracteres que estoy analizando y los comparo con la cadena "abcde", si son iguales devuelvo true
    string cadena = C.substr(p, q-p+1);
    sort(cadena.begin(), cadena.end());
    return (cadena == "abcde");
}

int SolucionDirecta(int p, int q) {     //Compruebo si la cadena cumple los requisitos con la función esCadenaValida, si los cumple devuelvo la posición del primer caracter, sino devuelvo -1
    if (esCadenaValida(p, q)) {
        return (p+1);
    }
    return -1;
}

set<int> concatenarConjuntos(const set<int>& s1, const set<int>& s2, const set<int>& s3) {  //Concateno los tres conjuntos resultantes de analizar la cadena izquierda, la cadena derecha y la frontera al unir las cadenas
    set<int> resultado;

    resultado.insert(s1.begin(), s1.end());
    resultado.insert(s2.begin(), s2.end());
    resultado.insert(s3.begin(), s3.end());

    return resultado;
}

set<int> Combinar(int p, int m, set<int> s1, set<int> s2) {     //Analizo la frontera reutilizando la función SolucionDirecta, cuando he terminado concateno los tres sets en 1
    set<int> SolucionFrontera;

    for (int i = max(m-3, p); i <= m; i++) {
        int n = SolucionDirecta(i, i+4);
        if (n != -1) {
            SolucionFrontera.insert(n);
        }
    }

    return concatenarConjuntos(s1, s2, SolucionFrontera);
}

set<int> DyV(int p, int q) {       //Función DyV (algoritmo principal)
    if (Pequeño(p, q)) {
        set<int> solucion;
        int n = SolucionDirecta(p, q);
        if (n != -1) {
            solucion.insert(n);
        }
        return solucion;
    } else {
        int m = Dividir(p, q);
        set<int> s1 = DyV(p, m);
        set<int> s2 = DyV(m+1, q);
        return Combinar(p, m, s1, s2);
    }
}

int main() {
    set<int> result = DyV(0, C.size() - 1);

    cout << "Número total de subcadenas encontradas: " << result.size() << endl;
    cout << "Posiciones de las subcadenas encontradas: ";

    for (int i : result) {
        cout << i << " ";
    }

    return 0;
}
