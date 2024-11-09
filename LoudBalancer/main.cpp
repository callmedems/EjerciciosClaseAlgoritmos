#include <iostream>
#include <vector>
#include <ctime>
#include "loadbalancer.h"
#include "loadbalancer.cpp"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializa aleatoriedad para los costos

    int numServers;
    cout << "Ingrese el número de servidores: ";
    cin >> numServers;

    vector<vector<int>> matrix(numServers, vector<int>(numServers));
    cout << "Generando costos de conexión entre servidores aleatoriamente...\n";

    // Genera aleatoriamente la matriz de costos de conexión
    for (int i = 0; i < numServers; i++) {
        for (int j = 0; j < numServers; j++) {
            if (i == j) {
                matrix[i][j] = 0;  // Costo 0 para conexiones consigo mismo
            } else {
                matrix[i][j] = rand() % 20 + 1;  // Costo aleatorio entre 1 y 20
            }
        }
    }

    int maxRequests;
    cout << "Ingrese la carga máxima por servidor: ";
    cin >> maxRequests;

    loadbalancer lb(numServers, matrix, maxRequests);

    int action, startServer;
    while (true) {
        cout << "\nOpciones:\n1. Asignar solicitud\n2. Completar solicitud\n3. Mostrar estado de servidores\n4. Salir\nOpción: ";
        cin >> action;

        switch (action) {
            case 1:
                cout << "Ingrese el servidor de origen para la solicitud: ";
                cin >> startServer;
                lb.distributeRequest(startServer);
                break;
            case 2:
                cout << "Ingrese el servidor para completar solicitud: ";
                cin >> startServer;
                lb.completeRequest(startServer);
                break;
            case 3:
                lb.displayServerLoads();
                break;
            case 4:
                return 0;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}
