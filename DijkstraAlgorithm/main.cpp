#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <iomanip> // para las distancias en decimales

using namespace std;

// constante para representar "infinito"
const double INF = numeric_limits<double>::infinity();

// Función de Dijkstra 
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

// imprimir el camino desde el nodo de origen hasta el nodo destino
void imprimirCamino(int origen, int destino, const vector<int>& previo) {
    stack<int> ruta;
    for (int v = destino; v != origen; v = previo[v]) {
        ruta.push(v);
    }
    ruta.push(origen);

    cout << "Camino elegido: ";
    while (!ruta.empty()) {
        cout << ruta.top() + 1; // ajustar para mostrar el nodo como 1 a 9
        ruta.pop();
        if (!ruta.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int n = 9; // número de nodos
    vector<vector<pair<int, double>>> grafo(n);
    vector<int> previo(n, -1);

    // aristas con pesos (distancias en metros) según la tabla
    grafo[0].push_back({1, 82.53});
    grafo[1].push_back({0, 82.53}); // Bidireccional

    grafo[1].push_back({2, 46.77});
    grafo[2].push_back({1, 46.77}); // Bidireccional

    grafo[2].push_back({3, 56.63});
    grafo[3].push_back({2, 56.63}); // Bidireccional

    grafo[3].push_back({4, 40.55});
    grafo[4].push_back({3, 40.55}); // Bidireccional

    grafo[4].push_back({5, 87.04});
    grafo[5].push_back({4, 87.04}); // Bidireccional

    grafo[5].push_back({6, 52.47});
    grafo[6].push_back({5, 52.47}); // Bidireccional

    grafo[6].push_back({7, 118.62});
    grafo[7].push_back({6, 118.62}); // Bidireccional

    grafo[7].push_back({8, 40.98});
    grafo[8].push_back({7, 40.98}); // Bidireccional

    grafo[8].push_back({0, 121.42});
    grafo[0].push_back({8, 121.42}); // Bidireccional

    grafo[2].push_back({5, 52.69});  // De nodo 3 a nodo 6
    grafo[5].push_back({2, 52.69});  // Bidireccional

    grafo[4].push_back({7, 38.90});  // De nodo 5 a nodo 8
    grafo[7].push_back({4, 38.90});  // Bidireccional

    // Verificación de conexiones
    cout << "Conexiones de cada nodo:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Nodo " << i + 1 << ": ";
        for (const auto& vecino : grafo[i]) {
            cout << vecino.first + 1 << " (" << vecino.second << " m), ";
        }
        cout << endl;
    }

    int origen, destino;

    // solicitar al usuario el nodo de inicio y el nodo de destino
    cout << "\nIngrese el nodo de origen (1 a " << n << "): ";
    cin >> origen;
    cout << "Ingrese el nodo de destino (1 a " << n << "): ";
    cin >> destino;

    // verificar que los nodos ingresados sean válidos
    if (origen < 1 || origen > n || destino < 1 || destino > n) {
        cout << "Nodos inválidos. Asegúrese de que el origen y el destino estén entre 1 y " << n << "." << endl;
        return 1;
    }

    // convertir a índices de 0 a n-1
    origen -= 1;
    destino -= 1;

    // ejecutar Dijkstra
    vector<double> distancias = dijkstra(n, origen, grafo, previo);

    // mostrar las distancias mínimas y el camino desde el nodo origen al destino
    if (distancias[destino] != INF) {
        cout << "\nCalculando el camino más corto del Nodo " << origen + 1 << " al Nodo " << destino + 1 << "." << endl;
        imprimirCamino(origen, destino, previo);

        // formatear la salida de la distancia con 2 decimales y calcular en km
        cout << "Distancia total: " << fixed << setprecision(2) << distancias[destino] << " meters (" 
             << distancias[destino] / 1000 << " km)" << endl;

        // calcular pasos dados 
        int steps = 0;
        for (int v = destino; v != origen; v = previo[v]) {
            steps++;
        }
        steps++; // se incluye el nodo de origen
        cout << "Pasos dados: " << steps << " pasos." << endl;
    } else {
        cout << "No hay camino del Nodo " << origen + 1 << " al Nodo " << destino + 1 << "." << endl;
    }

    return 0;
}
