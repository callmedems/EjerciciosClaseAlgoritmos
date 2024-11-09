#include <iostream>
#include "loadbalancer.h"
#include "loadbalancer.cpp"

using namespace std;

int main() {
    int numServers;
    cout << "Ingresa el número de servidores: ";
    cin >> numServers;

    vector<vector<int>> matrix(numServers, vector<int>(numServers));
    cout << "Crea la matriz de costos de conexión. (Usa " << INF << " para conexiones inexistentes):" << endl;

    // Entrada de la matriz de costos de conexión
    for (int i = 0; i < numServers; i++) {
        for (int j = 0; j < numServers; j++) {
            cin >> matrix[i][j];
        }
    }

    int maxRequests;
    cout << "Ingresa la carga máxima por servidor: ";
    cin >> maxRequests;

    loadbalancer lb(numServers, matrix, maxRequests);

    int startServer, action;
    while (true) {
        cout << "\nOpciones:\n1. Asignar solicitud\n2. Completar solicitud\n3. Mostrar estado de servidores\n4. Salir\nOpción: ";
        cin >> action;

        switch(action) {
            case 1:
                cout << "Ingresa el servidor de origen para la solicitud: ";
                cin >> startServer;
                lb.distributeRequest(startServer);
                break;
            case 2:
                cout << "Ingresa el servidor para completar solicitud: ";
                cin >> startServer;
                lb.completeRequest(startServer);
                break;
            case 3:
                lb.displayServerLoads();
                break;
            case 4:
                return 0;
            default:
                cout << "Opción no válida. Intente de nuevo.";
        }
    }
    return 0;
}
