#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

};

class Stack {
    private: 
        Node* topNode;

    public:
        Stack(): topdNode(nullptr){

            void push(int value){
                Node* newNode = new Node();
                newNode->data = value;
                newNode->next = topNode;
                topNode = newNode;
            }
        }

    void pop(){
        if(isEmpty()) {
            cout << "El Stack está vacío: " << endl;
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    int top(){
        if(isEmpty()) {
            cout << "El Stack está vacío ";
            return -1
            }
        return topNode -> data;
    }

    bool isEmpty(){
        return topNode == nullptr;
    }
};