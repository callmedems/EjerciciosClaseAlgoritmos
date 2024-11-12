#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

const int INF = INT_MAX; // por si no hay conexión

class LoadBalancer { //  clase LoadBalancer para gestionar la distribución de peticiones entre servidores
    private:
        int numServers; 
        int maxRequests;
        vector<vector<int>> adjMatrix; 
        vector<int> requestsPerServer; 

    public:
        LoadBalancer(int numServers, const vector<vector<int>>& matrix, int maxRequests); 
        int distributeRequest(int startServer); 
        void completeRequest(int serverId);
        void displayServerLoads(); 
};

#endif // LOADBALANCER_H