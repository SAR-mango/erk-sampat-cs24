#ifndef FIBVEC_H
#define FIBVEC_H

#include <cstddef>

class FibVec {
    public:
        FibVec();
        ~FibVec();
        size_t capacity () const;
        size_t count () const;
        void insert(int value, size_t index);
        int lookup(size_t index) const;
        int pop();
        void push(int value);
        int remove(size_t index);
    private:
        int* vector = NULL;
        size_t fib(size_t n) const;
        size_t curr_size = 1;
        size_t curr_num_items = 0;
        size_t n = 2;
};

FibVec* create_fibvec();

#endif
