#include <stdexcept>
#include <iostream>
#include "Set.h"

void printNode(Node* node);

Set::Set() {
    mRoot = nullptr;
}

Set::Set(const Set& other) {
}

Set::Set(Set&& other) {
}

Set::~Set() {
}

size_t Set::clear() {
    return 0;
}

bool Set::contains(const std::string& value) const {
    return false;
}

size_t Set::count() const {
    if (mRoot == nullptr) {
        return 0;
    }
    return 1 + mRoot->count;
}

void Set::debug() {
}

size_t Set::insert(const std::string& value) {
    if (mRoot == nullptr) {
        mRoot = new Node;
        mRoot->data = value;
        mRoot->head = mRoot;
        return 1;
    }
    if (value.compare(mRoot->data) < 0) {
        if (mRoot->left == nullptr) {
            mRoot->left = new Node;
            mRoot->left->data = value;
            mRoot->count++;
            mRoot = mRoot->head;
            return 1;
        }
        Node* temp = mRoot;
        mRoot = mRoot->left;
        temp->count += insert(value);
    }
    if (value.compare(mRoot->data) > 0) {
        if (mRoot->right == nullptr) {
            mRoot->right = new Node;
            mRoot->right->data = value;
            mRoot->count++;
            mRoot = mRoot->head;
            return 1;
        }
        Node* temp = mRoot;
        mRoot = mRoot->right;
        temp->count += insert(value);
    }
    mRoot = mRoot->head;
    return 0;
}

const std::string& Set::lookup(size_t n) const {
    Node* node = mRoot;
    while (node != nullptr) {
        if (node->left != nullptr) {
            if (n == node->left->count + 1) {
                return node->data;
            }
            if (n < node->left->count + 1) {
                node = node->left;
                continue;
            }
        }
        node = node->right;
    }
    throw std::out_of_range("no such value exists.");
}

void Set::print() const {
    printNode(mRoot);
    std::cout << std::endl;
}

size_t Set::remove(const std::string& value) {
    if (mRoot->head == nullptr) {
        return 0;
    }
    if (mRoot->head->data == value) {
        if (mRoot->count == 0) {
            mRoot->head = nullptr;
            delete mRoot;
            mRoot = nullptr;
            return 1;
        }
        if (mRoot->left == nullptr && mRoot->right != nullptr) {
            mRoot->head = mRoot->right;
            delete mRoot;
            mRoot = mRoot->head;
            return 1;
        }
        if (mRoot->left != nullptr && mRoot->right == nullptr) {
            mRoot->head = mRoot->left;
            delete mRoot;
            mRoot = mRoot->head;
            return 1;
        }
        std::string data = mRoot->left->data;
        remove(data);
        mRoot->data = data;
        mRoot->count--;
        return 1;
    }
    if (mRoot->left->data == value) {
        if (mRoot->left->count == 0) {
            delete mRoot->left;
            mRoot->left = nullptr;
            mRoot = mRoot->head;
            return 1;
        }
        if (mRoot->left->left == nullptr && mRoot->left->right != nullptr) {
            Node* temp = mRoot->left->right;
            delete mRoot->left;
            mRoot->left = temp;
            mRoot = mRoot->head;
            mRoot->left->count--;
            return 1;
        }
        if (mRoot->left->left != nullptr && mRoot->left->right == nullptr) {
            Node* temp = mRoot->left->left;
            delete mRoot->left;
            mRoot->left = temp;
            mRoot = mRoot->head;
            mRoot->left->count--;
            return 1;
        }
        std::string data = mRoot->left->left->data;
        remove(data);
        mRoot->left->data = data;
        mRoot->count--;
        mRoot = mRoot->head;
        return 1;
    }
    if (mRoot->right->data == value) {
        if (mRoot->right->count == 0) {
            delete mRoot->right;
            mRoot->right = nullptr;
            mRoot = mRoot->head;
            return 1;
        }
        if (mRoot->right->left == nullptr && mRoot->right->right != nullptr) {
            Node* temp = mRoot->right->right;
            delete mRoot->right;
            mRoot->right = temp;
            mRoot = mRoot->head;
            mRoot->right->count--;
            return 1;
        }
        if (mRoot->right->left != nullptr && mRoot->right->right == nullptr) {
            Node* temp = mRoot->right->left;
            delete mRoot->right;
            mRoot->right = temp;
            mRoot = mRoot->head;
            mRoot->right->count--;
            return 1;
        }
        std::string data = mRoot->right->left->data;
        remove(data);
        mRoot->right->data = data;
        mRoot->count--;
        mRoot = mRoot->head;
        return 1;
    }
    if (value.compare(mRoot->data) < 0) {
        if (mRoot->left == nullptr) {
            return 0;
        }
        mRoot = mRoot->left;
        return remove(value);
    }
    if (mRoot->right == nullptr) {
        return 0;
    }
    mRoot = mRoot->right;
    return remove(value);
}

void printNode(Node* node) {
    if (node == nullptr) {
        std::cout << '-';
    }
    else if (node->left == nullptr && node->right == nullptr) {
        std::cout << node->data;
    }
    else {
        std::cout << '(';
        printNode(node->left);
        std::cout << ' ' << node->data << ' ';
        printNode(node->right);
        std::cout << ')';
    }
}
