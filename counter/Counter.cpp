#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
}

Counter::~Counter() {
}

void Counter::inc(const std::string& key, int by) {
    if (list.increment(key, by)) {
        num_keys++;
    }
    sum_counts += by;
}

void Counter::dec(const std::string& key, int by) {
    if (list.decrement(key, by)) {
        num_keys++;
    }
    sum_counts -= by;
}

void Counter::del(const std::string& key) {
    sum_counts -= get(key);
    if (list.remove(key)) {
        num_keys--;
    }
}

int Counter::get(const std::string& key) const {
    return list.lookup(key);
}

void Counter::set(const std::string& key, int count) {
    sum_counts -= get(key);
    sum_counts += count;
    if (list.update(key, count)) {
        num_keys++;
    }
}

size_t Counter::count() const {
    return num_keys;
}

int Counter::total() const {
    return sum_counts;
}

Counter::Iterator Counter::begin() const {
    Iterator itr(list.getHead());
    return itr;
}

Counter::Iterator Counter::end() const {
    Iterator itr(list.getHead(), true);
    return itr;
}
