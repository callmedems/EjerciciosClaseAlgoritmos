#include "loadbalancer.h"

loadbalancer::loadbalancer(int n, const vector<vector<int>>& matrix, int maxRequests)
    : numServers(n), adjMatrix(matrix), requestsPerServer(n, 0), maxRequestsPerServer(maxRequests) {}

int loadbalancer::distributeRequest(int startServer) {
    int minCost = INF;
    int selectedServer = -1;

    // Buscar el servidor con menor costo de conexión y que tenga capacidad disponible
    for (int i = 0; i < numServers; ++i) {
        if (i != startServer && adjMatrix[startServer][i] != INF && requestsPerServer[i] < maxRequestsPerServer) {
            if (adjMatrix[startServer][i] < minCost) {
                minCost = adjMatrix[startServer][i];
                selectedServer = i;
            }
        }
    }

    // Si se encontró un servidor disponible, asignar la solicitud
    if (selectedServer != -1) {
        requestsPerServer[selectedServer]++;
        cout << "Solicitud asignada al Servidor " << selectedServer
             << " desde Servidor " << startServer << ", Carga actual: "
             << requestsPerServer[selectedServer] << "\n";
    } else {
        cout << "No hay servidores disponibles desde el Servidor " << startServer << "\n";
    }

    return selectedServer;
}

void loadbalancer::completeRequest(int serverId) {
    if (serverId < 0 || serverId >= numServers || requestsPerServer[serverId] == 0) {
        cout << "Error: no hay solicitudes activas en el Servidor " << serverId << "\n";
        return;
    }

    requestsPerServer[serverId]--;
    cout << "Solicitud completada en el Servidor " << serverId
         << ", Carga actual: " << requestsPerServer[serverId] << "\n";
}

void loadbalancer::displayServerLoads() const {
    cout << "Cargas actuales de los servidores:\n";
    for (int i = 0; i < numServers; ++i) {
        cout << "Servidor " << i << ": " << requestsPerServer[i]
             << " solicitudes" << (requestsPerServer[i] >= maxRequestsPerServer ? " (LLENO)" : " (DISPONIBLE)") << "\n";
    }
}
