#include "AVLTree.h"
#include <algorithm>
#include <iostream>

using namespace std;


// constructor
AVLTree::AVLTree() : root(nullptr) {} // inicializar la raíz en nullptr

// destructor
AVLTree::~AVLTree() {
    while (root) {
        remove(root->key);
    }
}

// altura de un nodo
int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0; //si el nodo no existe, entonces devuelve 0
}

// balance de un nodo
int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// rotación a la derecha
Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* AVLTree::insertNode(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

Node* AVLTree::deleteNode(Node* node, int key) {
    if (!node) return node;

    if (key < node->key)
        node->left = deleteNode(node->left, key);
    else if (key > node->key)
        node->right = deleteNode(node->right, key);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (!node) return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(int key) {
    root = insertNode(root, key);
}

void AVLTree::remove(int key) {
    root = deleteNode(root, key);
}

bool AVLTree::search(int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) return true;
        current = key < current->key ? current->left : current->right;
    }
    return false;
}

void AVLTree::inOrder(Node* node) {
    if (node) {
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }
}

void AVLTree::inOrder() {
    inOrder(root);
    cout << endl;
}
