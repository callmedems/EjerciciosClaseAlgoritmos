#include "AVLTree.h"
#include "AVLTree.cpp"

using namespace std; 

int main() {
    AVLTree avl;

    // se insertan elementos en el arbol AVL
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    // mostrar elementos
    cout << "Elementos almacenados en el árbol en orden: ";
    avl.inOrder(); // imprimir en orden

    avl.remove(20); // eliminar elemento 20
    cout << "Después de remover un elemento en el árbol: ";
    avl.inOrder();

    // búsqueda de elementoss
    cout << "Buscando 25: " << (avl.search(25) ? "Elemento encontrado" : "Elemento no encontrado") << endl;
    cout << "Buscandp 20: " << (avl.search(20) ? "Elemento encontrado" : "Elemento no encontrado") << endl;

    return 0;
}
