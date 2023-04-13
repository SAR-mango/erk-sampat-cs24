#include "FibVec.h"
#include <stdexcept>


FibVec* create_fibvec() {
  return new FibVec();
}

FibVec::FibVec() {
    vector = new int[curr_size];
}
FibVec::~FibVec() {
    delete[] vector;
}
size_t FibVec::capacity() const {
    return curr_size;
}
size_t FibVec::count() const {
    return curr_num_items;
}
void FibVec::insert(int value, size_t index) {
    if (index > curr_num_items) {
        throw std::out_of_range();
    }
    if (index > curr_size - 1) {
        n++;
        curr_size = fib(n);
        int* new_vector = new int[curr_size];
        for (int i = 0; i < curr_size; i++) {
            new_vector[i] = vector[i];
        }
        delete[] vector;
        vector = new_vector;
    }
    if (index == curr_num_items) {
        curr_num_items++;
    }
    vector[index] = value;
}
int FibVec::lookup(size_t index) const {
    if (index > curr_num_items) {
        throw std::out_of_range();
    }
    return vector[index];
}
int FibVec::pop() {
    if (curr_num_items == 0) {
        throw std::underflow_error();
    }
    int i = vector[curr_num_items - 1];
    remove(curr_num_items - 1);
    curr_num_items--;
    return i;
}
void FibVec::push(int value) {
    insert(value, curr_num_items);
}
int remove(size_t index) {
    if (index > curr_num_items) {
        throw std::out_of_range();
    }
    int i = vector[index];
    curr_num_items--;
    if (curr_num_items < fib(n - 2)) {
        n--;
        curr_size = fib(n);
    }
    int* new_vector = new int[curr_size];
    for (int i = 0; i < curr_num_items; i++) {
        if (i < index) {
            new_vector[i] = vector[i];
        }
        else {
            new_vector[i] = vector[i + 1];
        }
    }
    delete[] vector;
    vector = new_vector;
    return i;
}
size_t fib(size_t n) const {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}