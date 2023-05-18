#include "Counter.h"

Iterator::Iterator(bool head = true) {
    if (head) {
        current_node = head;
    }
    else {
        current_node = tail;
    }
}

const std::string& Iterator::key() const {
    return current_node->key;
}

int Iterator::value() const {
    return current_node->count;
}

Iterator& operator Iterator::++ () {
    current_node = current_node->next;
    return current_node;
}

bool operator Iterator::== (const Iterator& other) const {
    if (current_node->key == other.key()) {
        return true;
    }
    return false;
}

bool operator Iterator::!= (const Iterator& other) const {
    if (current_node->key == other.key()) {
        return false;
    }
    return true;
}
