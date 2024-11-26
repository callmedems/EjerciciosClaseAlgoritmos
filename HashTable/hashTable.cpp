// HashTable.cpp
#include "HashTable.h"

// Constructor que inicializa la tabla con un tamaño dado
HashTable::HashTable(int size) : tableSize(size) {
    table.resize(tableSize);
}

// Función de hash que utiliza el operador módulo
int HashTable::hashFunction(int key) const {
    return key % tableSize;
}

// Inserta un elemento en la tabla
void HashTable::insert(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}

// Busca un elemento en la tabla
bool HashTable::search(int key) const {
    int index = hashFunction(key);
    for (int element : table[index]) {
        if (element == key) {
            return true;
        }
    }
    return false;
}

// Elimina un elemento de la tabla
void HashTable::remove(int key) {
    int index = hashFunction(key);
    table[index].remove(key);
}

// Muestra la tabla hash
void HashTable::display() const {
    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Índice " << i << ": ";
        for (int key : table[i]) {
            std::cout << key << " -> ";
        }
        std::cout << "nullptr\n";
    }
}