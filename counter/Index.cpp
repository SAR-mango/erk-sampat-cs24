#include "Index.h"

// Index Member Functions

Index::Index() {
    for (size_t i = 0; i < size; i++) {
        indices[i] = nullptr;
    }
}

Index::~Index() {
}

Node* Index::keyToNode(const std::string& key, size_t& index) const {
    const char* str = key.c_str();
    long hashVal = 0;
	while (*str != '\0') {
        hashVal = (hashVal << 4) + *(str++);
		long g = hashVal & 0xF0000000L;
		if (g != 0) {
            hashVal ^= g >> 24;
        }
		hashVal &= ~g;
	}
	index = size_t(hashVal % (size - 1));
    return indices[index];
}

void Index::updateIndex(size_t index, Node* node) {
    indices[index] = node;
}
