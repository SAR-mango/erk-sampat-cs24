#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
    std::string data = "";
    size_t count = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    static Node* head;
};

#endif
