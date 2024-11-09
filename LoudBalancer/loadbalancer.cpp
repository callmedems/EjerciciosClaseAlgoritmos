#include "loadbalancer.h"
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>

LoadBalancer::LoadBalancer(int numServers, int maxRequests) 
    : numServers(numServers), maxRequests(maxRequests) {
    serverLoad.resize(numServers, 0);
    generateCostMatrix();
}

void LoadBalancer::generateCostMatrix() {
    srand(time(0));
    costMatrix.resize(numServers, std::vector<int>(numServers, INT_MAX));

    for (int i = 0; i < numServers; ++i) {
        for (int j = 0; j < numServers; ++j) {
            if (i != j) {
                costMatrix[i][j] = rand() % 20 + 1; // Costos entre 1 y 20
            }
        }
    }
}

int LoadBalancer::findAvailableServer() {
    int minCost = INT_MAX;
    int chosenServer = -1;

    for (int i = 0; i < numServers; ++i) {
        if (serverLoad[i] < maxRequests) {
            int totalCost = 0;
            for (int j = 0; j < numServers; ++j) {
                if (i != j) {
                    totalCost += costMatrix[i][j];
                }
            }
            if (totalCost < minCost) {
                minCost = totalCost;
                chosenServer = i;
            }
        }
    }
    return chosenServer;
}

void LoadBalancer::addRequest() {
    int server = findAvailableServer();
    if (server == -1) {
        std::cout << "Todos los servidores están llenos. No se puede atender la petición.\n";
    } else {
        serverLoad[server]++;
        std::cout << "Petición asignada al servidor " << server << ".\n";
    }
}

void LoadBalancer::printStatus() {
    std::cout << "Estado de los servidores:\n";
    for (int i = 0; i < numServers; ++i) {
        std::cout << "Servidor " << i << ": " << serverLoad[i]
                  << " / " << maxRequests << " peticiones.\n";
        if (serverLoad[i] == maxRequests) {
            std::cout << "Servidor " << i << " está lleno.\n";
        }
    }
}
