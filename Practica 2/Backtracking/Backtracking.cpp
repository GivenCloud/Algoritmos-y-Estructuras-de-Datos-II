#include <iostream>
#include <vector>
using namespace std;

#define MAX_TAMANO 20

int precios[MAX_TAMANO+1][MAX_TAMANO+1];
int s[MAX_TAMANO+1];
int modelos[MAX_TAMANO+1];
int nivel, M, C, pact;

void rellenarMatriz() {     //Inicio la matriz con todos los valores a -1
	for (int i = 0; i <= MAX_TAMANO+1; i++) {
		for (int j = 0; j <= MAX_TAMANO; j++) {
			precios[i][j] = -1;
		}
	}
}

void leerMatriz(){  //Leo los valores de entrada y los guardo en la matriz
    cin >> M >> C;

    for (int filas = 1; filas <= C; filas++) {
        int tiposPrenda;
        cin >> tiposPrenda;
        modelos[filas] = tiposPrenda;

        for (int columnas = 1; columnas <= tiposPrenda; columnas++) {
            int valor;
            cin >> valor;
            precios[filas][columnas] = valor;
        } 
    }
}

void Generar(){ //Genero el siguiente hermano
	//Si no es 0 restamos antes de sumar
    if (s[nivel] != 0){
        pact = pact - precios[nivel][s[nivel]];  
    }
    s[nivel] = s[nivel] + 1;
    pact = pact + precios[nivel][s[nivel]];
}

bool Solucion(){
    //Si estamos en el ultimo nivel y el dinero gastado no es demasiado devolvemos true.
    return (nivel == C) && (pact <= M);
}

bool Criterio(int voa){	   //Función que comprueba si se cumplen los criterios para avanzar de nivel
    return (nivel < C) && (pact < M);
}

bool Mas_hermanos(){    //Función que comprueban si hay más hermanos que comprobar
    //devolvemos true si no es el último modelo
    return s[nivel] < modelos[nivel];

}

void Retroceder(){  //Función para retroceder de nivel
    //restamos del precio actual la prenda seleccionada y retrocedemos.
    pact = pact - precios[nivel][s[nivel]];
    s[nivel] = 0;
    nivel--;
}

int Backtracking () { //Algoritmo principal
	nivel = 1;
    pact = 0;
    int voa = -9999;
    do {
        Generar();
        if ((Solucion()) && (pact > voa)){
            voa = pact;
        }
        if (Criterio(voa)){
            nivel++;
        } else {
            //Si la solucion voa es la máxima cantidad de dinero entonces no hace falta revisar los hermanos (poda).
            while ((!Mas_hermanos() || voa == M) && (nivel > 0)){
                Retroceder();
            }
        }
    } while (nivel > 0);
    return voa;
}

int main () {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		rellenarMatriz();
		leerMatriz();
		for (int i = 0; i < MAX_TAMANO; i++){
			s[i] = 0;   //Inicializo el array que me indica el camino que he escogido a 0, 0 significa que ese nivel se tiene que analizar
		}

		int resultado = Backtracking();
		if (resultado == -9999){        //Imprimo soluciones
			cout << "no solution" << endl;
		} else {
			cout << resultado << endl;
		}
	}

	return 0;
}


