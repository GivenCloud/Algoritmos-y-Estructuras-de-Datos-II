#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generarEntradasAleatorias(int casosPrueba) {
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    cout << casosPrueba << endl;

    for (int i = 1; i <= casosPrueba; ++i) {
        //int presupuesto = rand() % (i * 10) + 1; // Generar presupuesto aleatorio entre 1 y 200
        //int numPrendas = rand() % i + 1;   // Generar número de prendas aleatorio entre 1 y 20

		int presupuesto = 1000;
		int numPrendas = i;

        cout << presupuesto << " " << numPrendas << endl;

        for (int j = 0; j < numPrendas; ++j) {
            //int numModelos = rand() % 25 + 1; // Generar número de modelos aleatorio entre 1 y 20
            int numModelos = numPrendas;
            cout << numModelos;

            for (int k = 0; k < numModelos; ++k) {
                int precio = rand() % 200 + 1; // Generar precio aleatorio entre 1 y 200
                cout << " " << precio;
            }

            cout << endl;
        }
    }
}

int main() {
    //int casosPrueba;
    //cout << "Ingrese el número de casos de prueba: ";
    //cin >> casosPrueba;

    generarEntradasAleatorias(35);

    return 0;
}
