#include "Heap.h"
#include <iostream>

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

int main() {
    Heap heap(8);
    //std::cout << heap.lookup(0).value << std::endl;
    heap.push("test1", 0.5);
    heap.push("test2", 0.6);
    std::cout << heap.lookup(0).value << std::endl;
    std::cout << heap.lookup(1).value << std::endl;
    std::cout << heap.lookup(2).value << std::endl;

    return 0;
}
