#include <iostream>
#include "loadbalancer.h"
#include "loadbalancer.cpp"
#include <vector>
#include <limits>

using namespace std; 

// para config la matriz adyacente
vector<vector<int>> configMatrixAdj(int numServers){
    vector<vector<int>> matrix(numServers, vector<int>(numServers, INF)); // inicializar matriz numServers x numServers
    
    cout << "Configuración de costos entre servidores: " << endl;
    for (int i = 0; i < numServers; i++) {
        for (int j = i + 1; j < numServers; j++) {
            int costo; 
            cout << "Conexión entre Servidor " << i << " y Servidor " << j << " (si no hay conexión, ingrese -1): ";
            cin >> costo;
            if (costo >= 0){ // solo se asigna un costo si es mayor o igual a 0
                matrix[i][j] = costo; 
                matrix[j][i] = costo; 
            }
        }
    }
    return matrix;
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
        cout << "\n0. Salir\n";
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
                cout << "Ingrese el servidor de origen para la petición: ";
                cin >> startServer;
                lb.distributeRequest(startServer);
                break;
            case 2:
                cout << "Ingrese el servidor donde completar una petición: ";
                cin >> startServer;
                lb.completeRequest(startServer);
                break;
            case 3: 
                lb.displayServerLoads();
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (option != 0);

    return 0;
}
