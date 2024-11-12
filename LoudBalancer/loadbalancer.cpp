#include "loadbalancer.h"

using namespace std;

LoadBalancer::LoadBalancer(int n, const std::vector<std::vector<int>>& matrix, int maxRequests)
    : numServers(n), adjMatrix(matrix), maxRequests(maxRequests), requestsPerServer(n, 0) {}


int LoadBalancer::distributeRequest(int startServer) {
    int costoMin = INF;
    int selectedServer = -1;

    for (int i = 0; i < numServers; ++i) {
        if (i != startServer && adjMatrix[startServer][i] != INF && requestsPerServer[i] < maxRequests) {
            if ((selectedServer == -1 || requestsPerServer[i] < requestsPerServer[selectedServer]) &&
                (adjMatrix[startServer][i] < costoMin)) {
                costoMin = adjMatrix[startServer][i];
                selectedServer = i;
            }
        }
    }

    if (selectedServer != -1) {
        requestsPerServer[selectedServer]++;
        cout << "Petición asignada al Servidor " << selectedServer
             << " desde Servidor " << startServer << ", Carga actual: "
             << requestsPerServer[selectedServer] << "\n";
    } else {
        cout << "Error: todos los servidores están llenos o no hay conexion disponible.\n";
    }
    return selectedServer;
}


void LoadBalancer::completeRequest(int serverId) {
    if(serverId < 0 || serverId >= numServers || requestsPerServer[serverId] == 0) {
        cout << "Error: no hay peticiones activas en el Servidor " << serverId << "\n";
        return;
    }

    requestsPerServer[serverId]--;
    cout << "Petición completada en el Servidor " << serverId
             << ", Carga actual: " << requestsPerServer[serverId] << "\n";
}

void LoadBalancer::displayServerLoads() {
    cout << "Cargas actuales de los servidores:\n";
    for (int i = 0; i < numServers; ++i) {
        cout << "Servidor " << i << ": " << requestsPerServer[i] << " peticiones\n";
    }
}