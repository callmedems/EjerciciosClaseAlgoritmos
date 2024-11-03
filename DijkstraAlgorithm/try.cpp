#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <iomanip> // para formatear las distancias

using namespace std;

// Constante para representar "infinito"
const double INF = numeric_limits<double>::infinity();

// Función de Dijkstra que devuelve distancias y permite rastrear el camino
vector<double> dijkstra(int n, int origen, const vector<vector<pair<int, double>>>& grafo, vector<int>& previo) {
    vector<double> distancias(n, INF);
    distancias[origen] = 0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, origen});

    while (!pq.empty()) {
        double distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (distancia_actual > distancias[nodo_actual]) continue;

        for (const auto& vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            double peso_arista = vecino.second;
            double nueva_distancia = distancia_actual + peso_arista;

            if (nueva_distancia < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = nueva_distancia;
                previo[nodo_vecino] = nodo_actual;
                pq.push({nueva_distancia, nodo_vecino});
            }
        }
    }

    return distancias;
}

// Función para imprimir el camino desde el nodo de origen hasta el nodo destino
void imprimirCamino(int origen, int destino, const vector<int>& previo) {
    stack<int> ruta;
    for (int v = destino; v != origen; v = previo[v]) {
        ruta.push(v);
    }
    ruta.push(origen);

    cout << "Camino elegido: ";
    while (!ruta.empty()) {
        cout << ruta.top();
        ruta.pop();
        if (!ruta.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int n = 9; // Número de nodos
    vector<vector<pair<int, double>>> grafo(n);
    vector<int> previo(n, -1);

    // Definir aristas con los pesos proporcionados
    grafo[0].push_back({1, 82.53});
    grafo[1].push_back({2, 46.77});
    grafo[2].push_back({3, 56.63});
    grafo[3].push_back({4, 40.55});
    grafo[4].push_back({5, 87.04});
    grafo[5].push_back({6, 52.47});
    grafo[6].push_back({7, 118.62});
    grafo[7].push_back({8, 40.98});
    grafo[8].push_back({0, 121.42}); // Cierre del ciclo de nodo 9 a nodo 1

    int origen, destino;

    // Solicitar al usuario el nodo de inicio y el nodo de destino
    cout << "Ingrese el nodo de origen (0 a " << n-1 << "): ";
    cin >> origen;
    cout << "Ingrese el nodo de destino (0 a " << n-1 << "): ";
    cin >> destino;

    // Verificar que los nodos ingresados sean válidos
    if (origen < 0 || origen >= n || destino < 0 || destino >= n) {
        cout << "Nodos inválidos. Asegúrese de que el origen y el destino estén entre 0 y " << n-1 << "." << endl;
        return 1;
    }

    // Ejecutar Dijkstra
    vector<double> distancias = dijkstra(n, origen, grafo, previo);

    // Mostrar las distancias mínimas y el camino desde el nodo origen al destino
    if (distancias[destino] != INF) {
        cout << "Calculando el camino más corto del Nodo " << origen << " al Nodo " << destino << "." << endl;
        imprimirCamino(origen, destino, previo);

        // Imprimir la distancia total con dos decimales y en kilómetros
        cout << "Distancia total: " << fixed << setprecision(2) << distancias[destino] << " metros (" 
             << distancias[destino] / 1000 << " km)" << endl;

        // Calcular el número de pasos
        int pasos = 0;
        for (int v = destino; v != origen; v = previo[v]) {
            pasos++;
        }
        pasos++; // Incluir el nodo de origen
        cout << "Pasos dados: " << pasos << " pasos." << endl;
    } else {
        cout << "No hay camino del Nodo " << origen << " al Nodo " << destino << "." << endl;
    }

    return 0;
}
