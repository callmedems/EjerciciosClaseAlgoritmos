#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class loadbalancer {
private:
    int numServers;
    vector<vector<int>> adjMatrix;
    vector<int> requestsPerServer;
    int maxRequestsPerServer;

public:
    loadbalancer(int n, const vector<vector<int>>& matrix, int maxRequests);
    int distributeRequest(int startServer);
    void completeRequest(int serverId);
    void displayServerLoads() const;
};

#endif // LOADBALANCER_H
