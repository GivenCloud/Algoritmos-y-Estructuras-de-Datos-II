#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

string generarCadenaTamañoAleatorio() {
    srand(time(0));

    int tamaño = 100000; // Entre 10^4 y 10^6
    string caracteres = "abcdef";
    string cadenaGenerada;

    for (int i = 0; i < tamaño; i++) {
        int indiceCaracter = rand() % caracteres.length();
        cadenaGenerada += caracteres[indiceCaracter];
    }

    return cadenaGenerada;
}

string C = generarCadenaTamañoAleatorio();

bool Pequeño(int p, int q) {
    return (q-p+1 <= 5);
}

int Dividir(int p, int q) {
    return (p+q) / 2;
}

bool esCadenaValida(int p, int q) {
    string cadena = C.substr(p, q-p+1);
    sort(cadena.begin(), cadena.end());
    return (cadena == "abcde");
}

int SolucionDirecta(int p, int q) {
    if (esCadenaValida(p, q)) {
        return (p+1);
    }
    return -1;
}

set<int> concatenarConjuntos(const set<int>& s1, const set<int>& s2, const set<int>& s3) {
    set<int> resultado;

    resultado.insert(s1.begin(), s1.end());
    resultado.insert(s2.begin(), s2.end());
    resultado.insert(s3.begin(), s3.end());

    return resultado;
}

set<int> Combinar(int p, int m, set<int> s1, set<int> s2) {
    set<int> SolucionFrontera;

    for (int i = max(m-3, p); i <= m; i++) {
        int n = SolucionDirecta(i, i+4);
        if (n != -1) {
            SolucionFrontera.insert(n);
        }
    }

    return concatenarConjuntos(s1, s2, SolucionFrontera);
}

set<int> DyV(int p, int q) {
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

pair<bool, unordered_map<int, int>> tieneRepetidos(const set<int>& conjuntoEnteros) {
    unordered_map<int, int> contador;

    for (int elemento : conjuntoEnteros) {
        // Incrementamos el contador para cada elemento
        contador[elemento]++;
    }

    bool hayRepetidos = false;
    unordered_map<int, int> repetidos;

    // Buscamos elementos con contador mayor que 1 (repetidos)
    for (const auto& par : contador) {
        if (par.second > 1) {
            hayRepetidos = true;
            repetidos[par.first] = par.second;  // Guardamos el elemento y su cantidad
        }
    }

    return {hayRepetidos, repetidos};
}

int main() {
    set<int> result = DyV(0, C.size() - 1);

    cout << "Número total de subcadenas encontradas: " << result.size() << endl;
    cout << "Posiciones de las subcadenas encontradas: ";

    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    auto resultado = tieneRepetidos(result);

    if (resultado.first) {
        cout << "El conjunto tiene elementos repetidos." << endl;
        cout << C << endl;
        cout << "Elementos repetidos y su cantidad:" << endl;
        for (const auto& par : resultado.second) {
            cout << par.first << ": " << par.second << " veces" << endl;
        }
    } else {
        cout << "El conjunto no tiene elementos repetidos." << endl;
    }

    auto iterator = result.begin();
    for (auto i : result) {
        cout << "Cadena: ";
        for (int j = i-1; j <= i+3; j++) {
            cout << C[j];
        }
        cout << endl;
    }

    return 0;
}
