#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <optional>

enum CollisionResolution { LINEAR_PROBING, QUADRATIC_PROBING };

class HashTable {
private:
    int size;                           // Tamaño de la tabla
    std::vector<std::optional<int>> table; // Tabla que almacena claves
    int numElements;                    // Número de elementos en la tabla
    CollisionResolution collisionResolutionMethod; // Método de resolución de colisiones

    int hashFunction(int key);
    int probeLinear(int hash, int i);
    int probeQuadratic(int hash, int i);
    void rehash();
    int resolve(int hash, int i, int currentSize = -1);

public:
    HashTable(int tableSize, CollisionResolution method);

    void insert(int key);
    bool search(int key);
    void remove(int key);
    void display();
};

#endif // HASHTABLE_H
