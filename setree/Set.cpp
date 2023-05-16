#include <stdexcept>
#include <iostream>
#include "Set.h"

void printNode(Node* node);
std::string maxValueBelow(Node* node);
Node* lookupNode(size_t n, Node* root);
void printDebug(std::string garbage);
void updateCounts(Node* root, Node* parent);

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
        mRoot->head = nullptr;
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
    mRoot->head = nullptr;
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
        printDebug("doesn't contain");
        return 0;
    }
    if (mRoot->data == value) {
        if (mRoot->count == 0) {
            printDebug("removing root; root is the only element");
            clear();
            return 1;
        }
        else if (mRoot->left == nullptr && mRoot->right != nullptr) {
            printDebug("removing root; root has a right child");
            Node* temp = mRoot->right;
            delete mRoot;
            mRoot = temp;
            mRoot->head = temp;
            return 1;
        }
        else if (mRoot->left != nullptr && mRoot->right == nullptr) {
            printDebug("removing root; root has a left child");
            Node* temp = mRoot->left;
            delete mRoot;
            mRoot = temp;
            mRoot->head = temp;
            return 1;
        }
        else {
            printDebug("removing root; root has two children");
            std::string str = maxValueBelow(mRoot);
            remove(str);
            mRoot->data = str;
            return 1;
        }
    }
    size_t n = count() - 1;
    size_t m = n;
    while (n > 0) {
        if (lookup(n) == value) {
            break;
        }
        n--;
    }
    printDebug("found n of node to remove");
    Node* rm_node = lookupNode(n, mRoot);
    Node* parent = lookupNode(m, mRoot);
    while (parent->left != rm_node && parent->right != rm_node) {
        m--;
        parent = lookupNode(m, mRoot);
    }
    printDebug("found parent");
    if (rm_node->left == nullptr && rm_node->right == nullptr) {
        /*size_t q = n + 1;
        while (q <= o) {
            Node* node = lookupNode(o, mRoot);
            if (node->count > 0) {
                node->count--;
            }
            o--;
        }*/
        updateCounts(mRoot, parent);
        printDebug("updated counts");
        if (parent->left == rm_node) {
            printDebug("node to remove is a child, and is to the left of its parent");
            parent->left = nullptr;
        }
        else {
            printDebug("node to remove is a child, and is to the right of its parent");
            parent->right = nullptr;
        }
        printDebug("deleting node with no children");
        delete rm_node;
        return 1;
    }
    else if (rm_node->left != nullptr && rm_node->right == nullptr) {
        /*size_t q = n + 1;
        while (q <= o) {
            Node* node = lookupNode(o, mRoot);
            if (node->count == 2) {
                node->count--;
            }
            o--;
        }*/
        updateCounts(mRoot, parent);
        printDebug("updated counts");
        if (parent->left == rm_node) {
            printDebug("node to remove has something to its left, and this is being assigned to the left of its parent");
            parent->left = rm_node->left;
        }
        else {
            printDebug("node to remove has something to its left, and this is being assigned to the right of its parent");
            parent->right = rm_node->left;
        }
        delete rm_node;
        return 1;
    }
    else if (rm_node->left == nullptr && rm_node->right != nullptr) {
        /*size_t q = n + 1;
        while (q <= o) {
            Node* node = lookupNode(o, mRoot);
            if (node->count > 0) {
                node->count--;
            }
            o--;
        }*/
        updateCounts(mRoot, parent);
        printDebug("updated counts");
        if (parent->left == rm_node) {
            parent->left = rm_node->right;
            printDebug("node to remove has something to its right, and this is being assigned to the left of its parent");
        }
        else {
            printDebug("node to remove has something to its right, and this is being assigned to the right of its parent");
            parent->right = rm_node->right;
        }
        delete rm_node;
        return 1;
    }
    else {
        printDebug("node to remove has two children unfortunately; recursing");
        std::string str = maxValueBelow(rm_node);
        remove(str);
        rm_node->data = str;
        return 1;
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
        //std::cout << '[' << node->data << ']' << "[c]" << node->count << "[l]" << node->left << "[r]" << node->right;
        std::cout << '[' << node->data << ']' << "[c]" << node->count;
    }
    else {
        std::cout << '(';
        printNode(node->left);
        //std::cout << ' ' << '[' << node->data << ']' << "[c]" << node->count << "[l]" << node->left << "[r]" << node->right << ' ';
        std::cout << ' ' << '[' << node->data << ']' << "[c]" << node->count << ' ';
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

void printDebug(std::string garbage) {
    //std::cout << garbage << std::endl;
}

void updateCounts(Node* root, Node* parent) {
    while (root != parent) {
        root->count--;
        if (root->data.compare(parent->data) < 0) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    parent->count--;
}
