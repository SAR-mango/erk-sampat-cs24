#include "DataStore.h"

// DataStore Member Functions
DataStore::DataStore() {
    // set head and tail
}

DataStore::~DataStore() {
}

bool DataStore::increment(const std::string& key, int by) {
    size_t index;
    Node* node = index.keyToNode(key, index);
    if (node == nullptr) { // key isn't already present
        index.updateIndex(index, append(key, by));
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
    size_t index;
    Node* node = index.keyToNode(key, index);
    if (node == nullptr) { // key isn't already present
        index.updateIndex(index, append(key, -1 * by));
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
    size_t index;
    Node* node = index.keyToNode(key, index);
    if (node == nullptr) { // key isn't already present
        index.updateIndex(index, append(key, by));
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
                    right->dll_pos->count = by;
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
        node->count = by;
        return false;
    }
}

bool DataStore::remove(const std::string& key) {
    size_t index;
    Node* node = index.keyToNode(key, index);
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
        deleteNode(node);
        return true;
    }
}

int DataStore::lookup(const std::string& key) const {
    size_t index;
    Node* node = index.keyToNode(key, index);
    if (node == nullptr) { // key isn't already present
    }
    else if (node->key != key) { // index conflict; key may or may not be present
    }
    else { // correct key is present
    }
}

Node* DataStore::append(const std::string& key, int count);
void deleteNode(Node* node);

class DataStore {
    public:
    DataStore();
    ~DataStore();
    bool increment(const std::string& key, int by);
    bool decrement(const std::string& key, int by);
    bool update(const std::string& key, int count);
    bool remove(const std::string& key);
    int lookup(const std::string& key) const;

    private:
    Node* append(const std::string& key, int count);
    void deleteNode(Node* node);

    Index index;
    Node* head = new Node;
    Node* tail = new Node;
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
}
class Index {
    public:
    Index();
    ~Index();
    Node* keyToNode(const std::string& key, size_t& index = 0);
    void updateIndex(size_t& index, Node* node);

    private:
    size_t size = 10000;
    Node* indices[10000];
};
