#include <iostream>
#include "hashTable.h"
#include "hashTable.cpp"

using namespace std;

void displayMenu() {
    cout << "\n=== Tabla Hash ===\n";
    cout << "1. Insertar clave\n";
    cout << "2. Buscar clave\n";
    cout << "3. Eliminar clave\n";
    cout << "4. Mostrar tabla\n";
    cout << "5. Salir\n";
    cout << "Elija una opción: ";
}

int main() {
    int tableSize;
    int methodChoice;

    // Configuración inicial
    cout << "Ingrese el tamaño de la tabla: ";
    cin >> tableSize;

    cout << "Elija el método de resolución de colisiones:\n";
    cout << "1. Linear Probing\n";
    cout << "2. Quadratic Probing\n";
    cin >> methodChoice;

    CollisionResolution method = (methodChoice == 1) ? LINEAR_PROBING : QUADRATIC_PROBING;

    // Crear instancia de la hash table
    HashTable ht(tableSize, method);

    int choice, key;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: // Insertar clave
                cout << "Ingrese la clave a insertar: ";
                cin >> key;
                ht.insert(key);
                break;

            case 2: // Buscar clave
                cout << "Ingrese la clave a buscar: ";
                cin >> key;
                if (ht.search(key)) {
                    cout << "Clave encontrada.\n";
                } else {
                    cout << "Clave no encontrada.\n";
                }
                break;

            case 3: // Eliminar clave
                cout << "Ingrese la clave a eliminar: ";
                cin >> key;
                ht.remove(key);
                break;

            case 4: // Mostrar tabla
                ht.display();
                break;

            case 5: // Salir
                cout << "Saliendo del programa.\n";
                break;

            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
