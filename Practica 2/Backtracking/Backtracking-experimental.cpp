#include <iostream>
#include <sys/time.h>
using namespace std;

#define MAX_TAMANO 40

int precios[MAX_TAMANO+1][MAX_TAMANO+1];
int s[MAX_TAMANO+1];
int modelos[MAX_TAMANO+1];
int nivel, M, C, pact;

void rellenarMatriz() {
	for (int i = 0; i <= MAX_TAMANO+1; i++) {
		for (int j = 0; j <= MAX_TAMANO; j++) {
			precios[i][j] = -1;
		}
	}
}

void leerMatriz(){
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

void Generar(){
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

bool Criterio(int voa){	
    return (nivel < C) && (pact < M);
}

bool Mas_hermanos(){
    //devolvemos true si no es el último modelo .
    return s[nivel] < modelos[nivel];

}

void Retroceder(){
    //restamos del precio actual la prenda seleccionada y retrocedemos.
    pact = pact - precios[nivel][s[nivel]];
    s[nivel] = 0;
    nivel--;
}

int Backtracking () {
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
		struct timeval ti, tf;
        double tiempo;
        gettimeofday(&ti, NULL);
		
		rellenarMatriz();
		leerMatriz();
		for (int i = 0; i < MAX_TAMANO; i++){
			s[i] = 0;
		}

		int resultado = Backtracking();
		
		gettimeofday(&tf, NULL); // Instante final
        tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
        cout << C << ";" << tiempo << endl;
		
		
		if (resultado == -9999){
			//cout << "no solution" << endl;
		} else {
			//cout << resultado << endl;
		}
		
	}

	return 0;
}


