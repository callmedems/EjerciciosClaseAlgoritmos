#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>

using namespace std;

class HashTable {
private:
    vector<list<int>> table;
    int tableSize;

    // Función de hash que utiliza el operador módulo
    int hashFunction(int key) const;

public:
    // Constructor
    HashTable(int size);

    // Métodos de la tabla hash
    void insert(int key);
    bool search(int key) const;
    void remove(int key);
    void display() const;
};

#endif // HASHTABLE_H