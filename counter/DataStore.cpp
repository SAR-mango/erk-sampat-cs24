#include "DataStore.h"

// DataStore Member Functions
DataStore::DataStore() {
}

DataStore::~DataStore() {
}

bool DataStore::increment(const std::string& key, int by) {
    size_t index;
    Node* node = index.keyToNode(key, index);
    if (node == nullptr) { // key isn't already present
    }
    else if (node->key != key) { // index conflict; key may or may not be present
    }
    else { // correct key is present
        node->count += by;
        return false;
    }
}

bool DataStore::decrement(const std::string& key, int by) {
}

bool DataStore::update(const std::string& key, int count) {
}

bool DataStore::remove(const std::string& key) {
}

int DataStore::lookup(const std::string& key) {
}

void DataStore::append(const std::string& key, int count);

class DataStore {
    public:
    DataStore();
    ~DataStore();
    bool increment(const std::string& key, int by);
    bool decrement(const std::string& key, int by);
    bool update(const std::string& key, int count);
    bool remove(const std::string& key);
    int lookup(const std::string& key);

    private:
    void append(const std::string& key, int count);

    Index index;
    Node* head = new Node;
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
