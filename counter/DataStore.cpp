#include "DataStore.h"

DataStore::DataStore() {
}

DataStore::~DataStore() {
    if (head == nullptr) {
    }
    else if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node* node = head;
        while (node != nullptr) {
            Node* temp = node;
            Right_Node* temp_right = node->right;
            while (temp_right != nullptr) {
                Right_Node* prev_right = temp_right;
                temp_right = temp_right->right;
                delete prev_right;
            }
            node = node->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }
}

bool DataStore::increment(const std::string& key, int by) {
    size_t idx;
    Node* node = index.keyToNode(key, idx);
    if (node == nullptr) { // key isn't already present
        index.updateIndex(idx, append(key, by));
        return true;
    }
    else if (node->key != key) { // index conflict; key may or may not be present
        Right_Node* right = node->right;
        if (right == nullptr) {
            node->right = new Right_Node;
            node->right->dll_pos = append(key, by);
            return true;
        }
        Right_Node* prev = right;
        while (right != nullptr) {
            if (right->dll_pos != nullptr) {
                if (right->dll_pos->key == key) {
                    right->dll_pos->count += by;
                    return false;
                }
            }
            prev = right;
            right = right->right;
        }
        prev->right = new Right_Node;
        prev->right->dll_pos = append(key, by);
        return true;
    }
    else { // correct key is present
        node->count += by;
        return false;
    }
}

bool DataStore::decrement(const std::string& key, int by) {
    size_t idx;
    Node* node = index.keyToNode(key, idx);
    if (node == nullptr) { // key isn't already present
        index.updateIndex(idx, append(key, -1 * by));
        return true;
    }
    else if (node->key != key) { // index conflict; key may or may not be present
        Right_Node* right = node->right;
        if (right == nullptr) {
            node->right = new Right_Node;
            node->right->dll_pos = append(key, -1 * by);
            return true;
        }
        Right_Node* prev = right;
        while (right != nullptr) {
            if (right->dll_pos != nullptr) {
                if (right->dll_pos->key == key) {
                    right->dll_pos->count -= by;
                    return false;
                }
            }
            prev = right;
            right = right->right;
        }
        prev->right = new Right_Node;
        prev->right->dll_pos = append(key, -1 * by);
        return true;
    }
    else { // correct key is present
        node->count -= by;
        return false;
    }
}


bool DataStore::update(const std::string& key, int count) {
    size_t idx;
    Node* node = index.keyToNode(key, idx);
    if (node == nullptr) { // key isn't already present
        index.updateIndex(idx, append(key, count));
        return true;
    }
    else if (node->key != key) { // index conflict; key may or may not be present
        Right_Node* right = node->right;
        if (right == nullptr) {
            node->right = new Right_Node;
            node->right->dll_pos = append(key, count);
            return true;
        }
        Right_Node* prev = right;
        while (right != nullptr) {
            if (right->dll_pos != nullptr) {
                if (right->dll_pos->key == key) {
                    right->dll_pos->count = count;
                    return false;
                }
            }
            prev = right;
            right = right->right;
        }
        prev->right = new Right_Node;
        prev->right->dll_pos = append(key, count);
        return true;
    }
    else { // correct key is present
        node->count = count;
        return false;
    }
}

bool DataStore::remove(const std::string& key) {
    size_t idx;
    Node* node = index.keyToNode(key, idx);
    if (node == nullptr) { // key isn't already present
        return false;
    }
    else if (node->key != key) { // index conflict; key may or may not be present
        Right_Node* right = node->right;
        if (right == nullptr) {
            return false;
        }
        Right_Node* prev = right;
        while (right != nullptr) {
            if (right->dll_pos != nullptr) {
                if (right->dll_pos->key == key) {
                    deleteNode(right->dll_pos);
                    prev->right = right->right;
                    delete right;
                    return true;
                }
            }
            prev = right;
            right = right->right;
        }
        return false;
    }
    else { // correct key is present
        if (node->right == nullptr) {
            index.updateIndex(idx, nullptr);
        }
        else {
            index.updateIndex(idx, node->right->dll_pos);
            node->right->dll_pos->right = node->right->right;
            delete node->right;
        }
        deleteNode(node);
        return true;
    }
}

int DataStore::lookup(const std::string& key) const {
    size_t idx;
    Node* node = index.keyToNode(key, idx);
    if (node == nullptr) { // key isn't already present
        return 0;
    }
    else if (node->key != key) { // index conflict; key may or may not be present
        Right_Node* right = node->right;
        if (right == nullptr) {
            return 0;
        }
        while (right != nullptr) {
            if (right->dll_pos != nullptr) {
                if (right->dll_pos->key == key) {
                    return right->dll_pos->count;
                }
            }
            right = right->right;
        }
        return 0;
    }
    else { // correct key is present
        return node->count;
    }
}

Node* DataStore::append(const std::string& key, int count) {
    if (head == nullptr) {
        head = new Node;
        head->key = key;
        head->count = count;
        tail = head;
        return tail;
    }
    if (head == tail) {
        tail->next = new Node;
        tail = tail->next;
        tail->prev = head;
        head->next = tail;
        tail->key = key;
        tail->count = count;
        return tail;
    }
    tail->next = new Node;
    Node* prev = tail;
    tail = tail->next;
    tail->prev = prev;
    tail->key = key;
    tail->count = count;
    return tail;
}

void DataStore::deleteNode(Node* node) {
    if (node == head) {
        if (head == tail) {
            delete node;
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = head->next;
        head->prev = nullptr;
        delete node;
        return;
    }
    if (node == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete node;
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    return;
}

Node* DataStore::getHead() const {
    return head;
}
