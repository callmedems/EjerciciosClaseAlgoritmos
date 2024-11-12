#include <iostream>
#include "loadbalancer.h"
#include "loadbalancer.cpp"
#include <vector>
#include <limits>

using namespace std; 

// para config la matriz adyacente
vector<vector<int>> configMatrixAdj(int numServes){
    vector<vector<int>> matrix(numServes, vector<int>(numServes, INF)); // inicializar matriz numServers x numServers
    
    cout << "Configuración de costos entre servidores: " << endl;
    for (int i = 0; i < numServes; i++) {
        for (int j = 0; j < numServes; j++) {
            int costo; 
            cout << "Conexión entre Servidor " << i << " y Servidor " << j << " (si no hay conexión, ingrese -1): ";
            cin >> costo;
            if (costo >= 0){ // solo se asigna un costo si es mayor o igual a 0
                matrix[i][j] = costo; 
                matrix[j][i] = costo; 
            }
        }
    }
}


int main() {
    int numServers;
    int maxRequests;

    cout << "Ingrese el número de servidores: ";
    cin >> numServers;
    auto matrix = configMatrixAdj(numServers);
    cout << "Ingrese la carga máxima por servidor: ";
    cin >> maxRequests;
    LoadBalancer lb(numServers, matrix, maxRequests);

    int option, startServer;
    do { // menu de opciones para usuario
        cout << "\nSalir\n";
        cout << "1. Añadir petición\n";
        cout << "2. Completar petición\n";
        cout << "3. Mostrar estado de los servidores\n";
        cout << "Seleccione una opción: ";
        cin >> option;

        switch (option) {
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            case 1:
                lb.distributeRequest(startServer);
                break;
            case 2:
                lb.completeRequest(startServer);
                break;
            case 3: 
                lb.displayServerLoads();
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (option != 4);

    return 0;
}
