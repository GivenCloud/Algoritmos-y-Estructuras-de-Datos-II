#include <iostream>
#include <ctime> 
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

int** generarMatriz(int n) {
    srand(time(nullptr));

    int** matriz = new int*[n];
    for (int i = 0; i < n; ++i) {
        matriz[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = rand() % 10; // Generar un número aleatorio en el rango de 0 a 9
        }
    }

    return matriz;
}

void maxDiversidad(int** matriz, int n, int m){
	
	int solucion[n];
	for (int i = 0; i < n; i++){
		solucion[i] = 0;
	}
	if (m <= 1){
		cout << 0 << endl;
		for (int i = 0; i < n; i++){
			cout << solucion[i] << " " << endl;
		}
		return;
	}
	
	int max = 0;
	int fila = -1;
	int columna = -1;
	int maximo = 0;
	int maximo1 = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (matriz[i][j] >= max){
				max = matriz[i][j];
				fila = i;   //Hay que sumarle 1 a la fila
				columna = j;   //Hay que sumarle 1 a la columna
			}
		}
	}
	//cout << "Este es el numero mas grande de la matriz: " << max << endl;
	max = matriz[fila][columna] + matriz[columna][fila];
	solucion[fila] = 1;
	solucion[columna] = 1;
	m = m - 2;
	
	while (m > 0){
		//cout << "Valor de m: " << m << endl;
		for (int j = 0; j < n; j++){
			int sumaBucle = 0;
			if (solucion[j] == 0 && j != columna){
				//cout << "Entro en la fila: " << columna << " y en la columna: " << j << endl;
				for (int i = 0; i < n; i++){
					//int sumaBucle = 0;
					if (solucion[i] == 1){
						//cout << "Sumo " << matriz[i][j] << " + " << matriz[j][i] << endl;
						sumaBucle = sumaBucle + matriz[i][j] + matriz[j][i];
						//cout << "Suma del bucle: " << sumaBucle << endl;
						maximo1 = sumaBucle;
					}
				}
				if (maximo < maximo1){
					//cout << "Guardo" << endl;
					maximo = maximo1;
					columna = j;
					//cout << "Este es el valor de maximo: " << maximo << endl;
				}
			}
		}
		//cout << "Valor de columna: " << columna << endl;
		max = max + maximo;
		solucion[columna] = 1;
		m--;
	}
	
	//cout << max << endl;
	for (int i = 0; i < n; i++){
		//cout << solucion[i] << " ";
	}
	//cout << endl;
}

int main (){

	for (int i = 50; i <= 5000; i=i+20){
        struct timeval ti, tf;
        double tiempo;
        gettimeofday(&ti, NULL);

		int** matriz = generarMatriz(i);
		maxDiversidad(matriz, i, i/2);

        gettimeofday(&tf, NULL); // Instante final
        tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
        cout << i << ";" << i/2  << ";" << tiempo << endl;
	}

}