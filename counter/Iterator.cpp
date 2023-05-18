#include "Counter.h"

Node* Counter::Iterator::fake = new Node;

Counter::Iterator::Iterator(Node* head, bool end) {
    if (!end || head == nullptr) {
        current_node = head;
    }
    else {
        current_node = fake;
    }
}

const std::string& Counter::Iterator::key() const {
    return current_node->key;
}

int Counter::Iterator::value() const {
    return current_node->count;
}

Counter::Iterator& Counter::Iterator::operator ++ () {
    this->current_node = current_node->next;
    if (current_node == nullptr) {
        current_node = fake;
    }
    return *this;
}

bool Counter::Iterator::operator == (const Counter::Iterator& other) const {
    if (current_node == other.current_node) {
        return true;
    }
    return false;
}

bool Counter::Iterator::operator != (const Counter::Iterator& other) const {
    if (current_node == other.current_node) {
        return false;
    }
    return true;
}
