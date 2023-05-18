#ifndef NODE_H
#define NODE_H

struct Node;
struct Right_Node;

struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;
    Right_Node* right = nullptr;
    std::string key = "";
    int count = 0;
};
struct Right_Node {
    Right_Node* right = nullptr;
    Node* dll_pos = nullptr;
};

#endif
