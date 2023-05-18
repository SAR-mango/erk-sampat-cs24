#ifndef DATASTORE_H
#define DATASTORE_H

// Space to implement a separate datastore class, if you choose to do so.
// This can make things simpler by clearly separating functionality.
// The DataStore is in charge of storing pairs in insertion order.

#include "Index.h"

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
    Node* head = nullptr;
    Node* tail = nullptr;
};

#endif
