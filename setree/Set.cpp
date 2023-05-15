#include <stdexcept>
#include <iostream>
#include "Set.h"

void printNode(Node* node);
//std::string maxValueBelow(Node* node);
Node* maxValueBelow(Node* node);
Node* deleteNode(Node* root, const std::string data);

Set::Set() {
    mRoot = nullptr;
}

Set::Set(const Set& other) {
}

Set::Set(Set&& other) {
}

Set::~Set() {
    clear();
}

size_t Set::clear() {
    if (mRoot == nullptr) {
        return 0;
    }
    if (mRoot->count == 0) {
        delete mRoot;
        mRoot = nullptr;
        return 1;
    }
    Node* original = mRoot;
    if (mRoot->left != nullptr) {
        if (mRoot->left->count == 0) {
            delete mRoot->left;
            mRoot->left = nullptr;
        }
        else {
            mRoot = mRoot->left;
            clear();
        }
    }
    mRoot = original;
    if (mRoot->right != nullptr) {
        if (mRoot->right->count == 0) {
            delete mRoot->right;
            mRoot->right = nullptr;
        }
        else {
            mRoot = mRoot->right;
            clear();
        }
    }
    mRoot = original;
    size_t count = mRoot->count;
    delete mRoot;
    mRoot = nullptr;
    return count + 1;
}

bool Set::contains(const std::string& value) const {
    if (mRoot == nullptr) {
        return false;
    }
    size_t n = count() - 1;
    while (n > 0) {
        if (lookup(n) == value) {
            return true;
        }
        n--;
    }
    if (lookup(n) == value) {
        return true;
    }
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
        size_t temp_count = temp->count;
        mRoot = mRoot->left;
        temp->count += insert(value);
        return temp->count - temp_count;
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
        size_t temp_count = temp->count;
        mRoot = mRoot->right;
        temp->count += insert(value);
        return temp->count - temp_count;
    }
    mRoot = mRoot->head;
    return 0;
}

const std::string& Set::lookup(size_t n) const {
    if (mRoot == nullptr) {
        throw std::out_of_range("no such value exists.");
    }
    Node* node = mRoot;
    size_t smallerCount = 0;
    if (node->left != nullptr) {
        smallerCount = node->left->count + 1;
    }
    while (node != nullptr) {
        if (n == smallerCount) {
            return node->data;
        }
        else if (n < smallerCount) {
            node = node->left;
            if (node != nullptr) {
                smallerCount--;
                if (node->right != nullptr) {
                    smallerCount -= node->right->count + 1;
                }
            }
        }
        else {
            node = node->right;
            if (node != nullptr) {
                smallerCount++;
                if (node->left != nullptr) {
                    smallerCount += node->left->count + 1;
                }
            }
        }
    }
    throw std::out_of_range("no such value exists.");
}

void Set::print() const {
    printNode(mRoot);
    std::cout << std::endl;
}

/*size_t Set::remove(const std::string& value) {
    if (!contains(value)) {
        return 0;
    }
    deleteNode(mRoot, value);
    return 1;
}*/

size_t Set::remove(const std::string& value) {
    if (mRoot == nullptr) {
        return 0;
    }
    Node* current = mRoot;
    Node* parent = nullptr;
    bool isLeftChild = false;
    while (current != nullptr && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->left;
            isLeftChild = true;
        }
        else {
            current = current->right;
            isLeftChild = false;
        }
    }
    if (current == nullptr) {
        return 0;
    }
    //size_t removedCount = current->count;
    if (current->left == nullptr && current->right == nullptr) {
        if (current == mRoot) {
            mRoot = nullptr;
        }
        else if (isLeftChild) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete current;
    }
    else if (current->left == nullptr) {
        if (current == mRoot) {
            mRoot = current->right;
        }
        else if (isLeftChild) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
        delete current;
    }
    else if (current->right == nullptr) {
        if (current == mRoot) {
            mRoot = current->left;
        }
        else if (isLeftChild) {
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
        delete current;
    }
    else {
        Node* successor = current->left;
        Node* successorParent = current;
        while (successor->right != nullptr) {
            successorParent = successor;
            successor = successor->right;
        }
        current->data = successor->data;
        current->count = successor->count;

        if (successorParent == current) {
            current->left = successor->left;
        }
        else {
            successorParent->right = successor->left;
        }
        delete successor;
    }
    //return removedCount;
    return 1;
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
/*void printNode(Node* node) { // goated for debugging
    if (node == nullptr) {
        std::cout << '-';
    }
    else if (node->left == nullptr && node->right == nullptr) {
        std::cout << '[' << node->data << ']' << "[c]" << node->count << "[l]" << node->left << "[r]" << node->right;
    }
    else {
        std::cout << '(';
        printNode(node->left);
        std::cout << ' ' << '[' << node->data << ']' << "[c]" << node->count << "[l]" << node->left << "[r]" << node->right << ' ';
        printNode(node->right);
        std::cout << ')';
    }
}*/

//std::string maxValueBelow(Node* node) {
Node* maxValueBelow(Node* node) {
    node = node->left;
    while (node->right != nullptr) {
        node = node->right;
    }
    //return node->data;
    return node;
}

Node* deleteNode(Node* root, const std::string data) {
    if (root == nullptr) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = maxValueBelow(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
