#include <stdexcept>
#include <iostream>
#include "Set.h"

void printNode(Node* node);
std::string maxValueBelow(Node* node);
Node* lookupNodeSubCount(size_t n, Node* root);
Node* lookupNode(size_t n, Node* root);

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

size_t Set::remove(const std::string& value) {
    if (!contains(value)) {
        return 0;
    }
    size_t n = count() - 1;
    while (n > 0) {
        if (lookup(n) == value) {
            break;
        }
        n--;
    }
    Node* remove_node = lookupNode(n, mRoot);
    if (remove_node->count == 0) {
        lookupNodeSubCount(n, mRoot);
        delete remove_node;
        remove_node = nullptr;
        return 1;
    }
    else if (remove_node->left == nullptr && remove_node->right != nullptr) {
        //lookupNodeSubCount(n, mRoot);
        Node* temp = remove_node->right;
        delete remove_node;
        remove_node = temp;
        return 1;
    }
    else if (remove_node->left != nullptr && remove_node->right == nullptr) {
        //lookupNodeSubCount(n, mRoot);
        Node* temp = remove_node->left;
        delete remove_node;
        remove_node = temp;
        return 1;
    }
    else {
        std::string temp = maxValueBelow(remove_node);
        size_t i = remove(temp);
        remove_node->data = temp;
        return i;
    }
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

std::string maxValueBelow(Node* node) {
    node = node->left;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node->data;
}

Node* lookupNodeSubCount(size_t n, Node* root) {
    size_t smallerCount = 0;
    if (root->left != nullptr) {
        smallerCount = root->left->count + 1;
    }
    while (root != nullptr) {
        if (n == smallerCount) {
            return root;
        }
        else if (n < smallerCount) {
            root->count--;
            Node* temp_root = root;
            root = root->left;
            if (root != nullptr) {
                smallerCount--;
                if (root->right != nullptr) {
                    smallerCount -= root->right->count + 1;
                }
            }
            if (n == smallerCount) {
                temp_root->left = nullptr;
            }
        }
        else {
            root->count--;
            Node* temp_root = root;
            root = root->right;
            if (root != nullptr) {
                smallerCount++;
                if (root->left != nullptr) {
                    smallerCount += root->left->count + 1;
                }
            }
            if (n == smallerCount) {
                temp_root->right = nullptr;
            }
        }
    }
    return nullptr;
}

Node* lookupNode(size_t n, Node* root) {
    size_t smallerCount = 0;
    if (root->left != nullptr) {
        smallerCount = root->left->count + 1;
    }
    while (root != nullptr) {
        if (n == smallerCount) {
            return root;
        }
        else if (n < smallerCount) {
            root = root->left;
            if (root != nullptr) {
                smallerCount--;
                if (root->right != nullptr) {
                    smallerCount -= root->right->count + 1;
                }
            }
        }
        else {
            root = root->right;
            if (root != nullptr) {
                smallerCount++;
                if (root->left != nullptr) {
                    smallerCount += root->left->count + 1;
                }
            }
        }
    }
    return nullptr;
}
