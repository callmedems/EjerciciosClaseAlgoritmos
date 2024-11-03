#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insertNode(Node* node, int key);
    Node* deleteNode(Node* node, int key);
    Node* minValueNode(Node* node);
    void inOrder(Node* node);

public:
    AVLTree();
    ~AVLTree();
    void insert(int key);
    void remove(int key);
    bool search(int key);
    void inOrder();
};

#endif
