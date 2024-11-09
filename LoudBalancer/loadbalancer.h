#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>

class LoadBalancer {
public:
    LoadBalancer(int numServers, int maxRequests);
    void addRequest();
    void printStatus();

private:
    int numServers;
    int maxRequests;
    std::vector<int> serverLoad;
    std::vector<std::vector<int>> costMatrix;

    void generateCostMatrix();
    int findAvailableServer();
};

#endif
