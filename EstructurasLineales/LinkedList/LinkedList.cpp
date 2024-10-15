// Teoría de Linked List

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
};

void addNode(Node* &head, int value) {
    Node* newNode = new Node(); // crear un nuevo nodo en memoria
    newNode -> data = value; // could be (*newNode).data = value? // ASIGNACION DE VALUE A LA ESTRUCTURA ACCEDIENDO A DATA
    newNode -> next = nullptr; // el siguiente nodo es nullptr
    if (head == nullptr) {
        head = newNode; // si la lista esta vacia, el nuevo nodo es el head
        } else {
            Node* temp = head; // crear una variable temporal que almacene el current head
            // recorremos la lista hasta el último nodo
            while (temp -> next != nullptr) {
                temp = temp -> next; // avanzar hasta el final de la lista
            }
            temp -> next = newNode; // enlazamos
        }
}

void showList(Node* head){
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp -> data << " " << endl;
        temp = temp -> next;
    }
}


int main(){

    
    Node* list = nullptr;
    addNode(list, 40);
    addNode(list, 10);
    addNode(list, 890);

    cout << "Lista de valor: " << endl;
    showList(list);

    return 0;
}