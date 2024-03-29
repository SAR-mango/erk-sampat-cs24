#ifndef INDEX_H
#define INDEX_H

// Space to implement a separate index class, if you choose to do so.
// This can make things simpler by clearly separating functionality.
// The Index is in charge of getting pairs from the DataStore by key.

#include <string>
#include "Nodes.h"

class Index {
    public:
    Index();
    ~Index();
    Node* keyToNode(const std::string& key, size_t& index) const;
    void updateIndex(size_t index, Node* node);

    private:
    size_t size = 200000;
    Node* indices[200000];
};

#endif
