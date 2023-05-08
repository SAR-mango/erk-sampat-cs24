#include "Node.h"

Node* Node::head = nullptr;

void setLeft(Node* &node) {
    node = node->left;
}

void setRight(Node* &node) {
    node = node->left;
}

void setHead(Node* &node) {
    node = node->head;
}
