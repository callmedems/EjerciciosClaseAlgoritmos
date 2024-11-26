#include "hashTable.h"
#include <iostream>
#include <stdexcept>

// Función de hash
int HashTable::hashFunction(int key) {
    return key % size;
}

// Resolución de colisiones: Linear Probing
int HashTable::probeLinear(int hash, int i) {
    return (hash + i) % size;
}

// Resolución de colisiones: Quadratic Probing
int HashTable::probeQuadratic(int hash, int i) {
    return (hash + i * i) % size;
}

// Rehashing
void HashTable::rehash() {
    int newSize = size * 2;
    std::vector<std::optional<int>> newTable(newSize);

    for (const auto& element : table) {
        if (element.has_value()) {
            int key = element.value();
            int hash = key % newSize;

            int i = 0;
            while (newTable[resolve(hash, i, newSize)].has_value()) {
                i++;
            }
            newTable[resolve(hash, i, newSize)] = key;
        }
    }

    table = newTable;
    size = newSize;
}

// Resolver colisiones según el método determinado
int HashTable::resolve(int hash, int i, int currentSize) {
    if (currentSize == -1) currentSize = size;

    if (collisionResolutionMethod == LINEAR_PROBING)
        return (hash + i) % currentSize;
    else if (collisionResolutionMethod == QUADRATIC_PROBING)
        return (hash + i * i) % currentSize;

    throw std::logic_error("Método de colisión no soportado.");
}

// Constructor
HashTable::HashTable(int tableSize, CollisionResolution method)
    : size(tableSize), table(tableSize), numElements(0), collisionResolutionMethod(method) {}

// Insertar una clave
void HashTable::insert(int key) {
    if (numElements >= 0.7 * size) {
        rehash();
    }

    int hash = hashFunction(key);
    int i = 0;

    while (table[resolve(hash, i)].has_value()) {
        if (table[resolve(hash, i)].value() == key) {
            std::cout << "Clave duplicada: " << key << std::endl;
            return;
        }
        i++;
    }

    table[resolve(hash, i)] = key;
    numElements++;
}

// Buscar una clave
bool HashTable::search(int key) {
    int hash = hashFunction(key);
    int i = 0;

    while (table[resolve(hash, i)].has_value()) {
        if (table[resolve(hash, i)].value() == key) {
            return true;
        }
        i++;
    }

    return false;
}

// Eliminar una clave
void HashTable::remove(int key) {
    int hash = hashFunction(key);
    int i = 0;

    while (table[resolve(hash, i)].has_value()) {
        if (table[resolve(hash, i)].value() == key) {
            table[resolve(hash, i)] = std::nullopt;
            numElements--;
            return;
        }
        i++;
    }

    std::cout << "Clave no encontrada: " << key << std::endl;
}

// Mostrar la tabla
void HashTable::display() {
    for (int i = 0; i < size; i++) {
        if (table[i].has_value()) {
            std::cout << i << ": " << table[i].value() << std::endl;
        } else {
            std::cout << i << ": -" << std::endl;
        }
    }
}
