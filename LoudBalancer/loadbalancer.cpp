#include "loadbalancer.h"

using namespace std;

// constructor que inicializa el número de servidores, matriz de adyacencia de costos y capacidad max de peticiones por servidor
LoadBalancer::LoadBalancer(int numServers, const vector<vector<int>>& matrix, int maxRquests)
    : numServers(numServers), adjMatrix(matrix), maxRequests(maxRequests), requestsPerServer(numServers, 0) {}

// distribuir una solicitud desde un servidor de inicio a otro servidor con menor costo y carga
int LoadBalancer::distributeRequest(int startServer) {
    int costoMin = INF;
    int selectedServer = -1;

    // itera para encontrar servidor óptimo
    for (int i = 0; i < numServers; ++i) {
        if (i != startServer && adjMatrix[startServer][i] != INF && requestsPerServer[i] < maxRequests) {
            if ((selectedServer == -1 || requestsPerServer[i] < requestsPerServer[selectedServer]) &&
                (adjMatrix[startServer][i] < costoMin)) {
                costoMin = adjMatrix[startServer][i];
                selectedServer = i;
            }
        }
    }

    if (selectedServer != -1) { // se encontró un servidor disponible, incrementa su carga y muestra el mensaje
        requestsPerServer[selectedServer]++;
        cout << "Petición asignada al Servidor " << selectedServer
             << " desde Servidor " << startServer << ", Carga actual: "
             << requestsPerServer[selectedServer] << "\n";
    } else {
        cout << "Error: todos los servidores están llenos o no hay conexion disponible.\n";
    }
    return selectedServer;
}

// completar una petición en un servidor dado
void LoadBalancer::completeRequest(int serverId) {
    if(serverId < 0 || serverId >= numServers || requestsPerServer[serverId] == 0) {
        cout << "Error: no hay peticiones activas en el Servidor " << serverId << "\n";
        return;
    }

    requestsPerServer[serverId]--;
    cout << "Petición completada en el Servidor " << serverId
             << ", Carga actual: " << requestsPerServer[serverId] << "\n";
}

// mostrar las cargas actuales de cada servidor
void LoadBalancer::displayServerLoads() {
    cout << "Cargas actuales de los servidores:\n";
    for (int i = 0; i < numServers; ++i) {
        cout << "Servidor " << i << ": " << requestsPerServer[i] << " solicitudes\n";
    }
}