#include "Set.h"

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
    return 0;
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
        mRoot = mRoot->left;
        return insert(value);
    }
    if (value.compare(mRoot->data) > 0) {
        if (mRoot->right == nullptr) {
            mRoot->right = new Node;
            mRoot->right->data = value;
            mRoot->count++;
            mRoot = mRoot->head;
            return 1;
        }
        mRoot = mRoot->right;
        return insert(value);
    }
    mRoot = mRoot->head;
    return 0;
}

const std::string& Set::lookup(size_t n) const {
    return mRoot->data;
}

void Set::print() const {
}

size_t Set::remove(const std::string& value) {
    if (mRoot->head == nullptr || mRoot->count == 0) {
        return 0;
    }
    if (mRoot->head->data == value) {
        if (mRoot->count == 0) {
            mRoot->head = nullptr;
            delete mRoot;
            mRoot = nullptr;
            return 1;
        }
        if (mRoot->count == 1) {
            if (mRoot->left == nullptr) {
                mRoot->head = mRoot->right;
                delete mRoot;
                mRoot = mRoot->head;
                return 1;
            }
            mRoot->head = mRoot->left;
            delete mRoot;
            mRoot = mRoot->head;
            return 1;
        }
        std::string data = mRoot->left->data;
        remove(data);
        mRoot->data = data;
        return 1;
    }
    if (mRoot->left->data == value) {
        if (mRoot->left->count == 0) {
            delete mRoot->left;
            mRoot->left = nullptr;
            mRoot = mRoot->head;
            return 1;
        }
        if (mRoot->left->count == 1) {
            if (mRoot->left->left == nullptr) {
                Node* temp = mRoot->left->left;
                delete mRoot->left;
                mRoot->left = temp;
                mRoot = mRoot->head;
                return 1;
            }
            Node* temp = mRoot->left->right;
            delete mRoot->left;
            mRoot->left = temp;
            mRoot = mRoot->head;
            return 1;
        }
        std::string data = mRoot->left->left->data;
        remove(data);
        mRoot->left->data = data;
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
        if (mRoot->right->count == 1) {
            if (mRoot->right->left == nullptr) {
                Node* temp = mRoot->right->left;
                delete mRoot->right;
                mRoot->right = temp;
                mRoot = mRoot->head;
                return 1;
            }
            Node* temp = mRoot->right->right;
            delete mRoot->right;
            mRoot->right = temp;
            mRoot = mRoot->head;
            return 1;
        }
        std::string data = mRoot->right->left->data;
        remove(data);
        mRoot->right->data = data;
        mRoot = mRoot->head;
        return 1;
    }
    if (value.compare(mRoot->data) < 0) {
        mRoot = mRoot->left;
        return remove(value);
    }
    mRoot = mRoot->right;
    return remove(value);
}
