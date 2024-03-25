#include <iostream>
using namespace std;

int** leerMatriz(int n, int m){  //Función para poder leer los datos de entrada y meterlos dentro de una matriz
	
	int** matriz = new int*[n];
	for (int i = 0; i < n; i++){
		matriz[i] = new int[m];
		for (int j = 0; j < m; j++){
			cin >> matriz[i][j];
		}
	} 
	return matriz;
}

void maxDiversidad(int** matriz, int n, int m){  //Función principal
	
	int solucion[n];
	for (int i = 0; i < n; i++){	//Inicializo el array solución a 0
		solucion[i] = 0;
	}
	if (m <= 1){	//Compruebo que m sea mayor que 1, ya que sino no se podría realizar, porque se necesita mínimo m = 2
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
		for (int j = 0; j < n; j++){	//Recorro la toda la matriz buscando el valor más grande
			if (matriz[i][j] >= max){
				max = matriz[i][j];
				fila = i;   //Hay que sumarle 1 a la fila
				columna = j;   //Hay que sumarle 1 a la columna
			}
		}
	}
	//cout << "Este es el numero mas grande de la matriz: " << max << endl;
	max = matriz[fila][columna] + matriz[columna][fila];	
	solucion[fila] = 1;			//En el array solución indico que he escogido tanto la fila como la columna del valor más grande de la matriz, por lo tanto, también le resto 2 a m
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
	
	cout << max << endl;
	for (int i = 0; i < n; i++){	//Imprimo las soluciones
		cout << solucion[i] << " ";
	}
	cout << endl;
}

int main (){
	int T, n, m;
	cin >> T;
	for (int i = 0; i < T; i++){
		cin >> n >> m;
		int** matriz = leerMatriz(n, n);
		maxDiversidad(matriz, n, m);
	}
}