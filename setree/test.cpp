#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

/* We are creating the following set:
    d
   / \
  b   e
 / \   \
a   c   f
         \
          q
         / \
        p   r
*/

int main() {
    Set set;

    set.insert("d");
    set.insert("b");
    set.insert("e");
    set.insert("a");
    set.insert("c");
    set.insert("f");
    set.insert("q");
    set.insert("r");
    set.insert("p");

    set.insert("f");
    set.insert("a");
    set.insert("f");
    set.insert("a");
    set.insert("f");
    set.insert("a");
    set.insert("f");
    set.insert("a");

    std::cout << "original set:" << std::endl;
    set.print();

    std::cout << "Count: " << set.count() << std::endl;
    std::cout << "Lookup n = 0: " << set.lookup(0) << std::endl;
    std::cout << "Lookup n = 1: " << set.lookup(1) << std::endl;
    std::cout << "Lookup n = 2: " << set.lookup(2) << std::endl;
    std::cout << "Lookup n = 3: " << set.lookup(3) << std::endl;
    std::cout << "Lookup n = 4: " << set.lookup(4) << std::endl;
    std::cout << "Lookup n = 5: " << set.lookup(5) << std::endl;
    std::cout << "Lookup n = 6: " << set.lookup(6) << std::endl;
    std::cout << "Lookup n = 7: " << set.lookup(7) << std::endl;
    std::cout << "Lookup n = 8: " << set.lookup(8) << std::endl;

    std::cout << "Contains 'd': " << set.contains("d") << std::endl;
    std::cout << "Contains 'b': " << set.contains("b") << std::endl;
    std::cout << "Contains 'e': " << set.contains("e") << std::endl;
    std::cout << "Contains 'a': " << set.contains("a") << std::endl;
    std::cout << "Contains 'c': " << set.contains("c") << std::endl;
    std::cout << "Contains 'f': " << set.contains("f") << std::endl;
    std::cout << "Contains 'q': " << set.contains("q") << std::endl;
    std::cout << "Contains 'r': " << set.contains("r") << std::endl;
    std::cout << "Contains 'p': " << set.contains("p") << std::endl;
    std::cout << "Contains \"random\": " << set.contains("random") << std::endl;
    
    std::cout << "Count: " << set.count() << ", cleared " << set.clear() << std::endl;
    set.print();
    set.insert("d");
    set.insert("b");
    set.insert("e");
    set.insert("a");
    set.insert("c");
    set.insert("f");
    set.insert("q");
    set.insert("r");
    set.insert("p");

    set.insert("f");
    set.insert("a");
    set.insert("f");
    set.insert("a");
    set.insert("f");
    set.insert("a");
    set.insert("f");
    set.insert("a");

    std::cout << "remove a" << std::endl;
    set.remove("a");
    set.print();
    std::cout << "remove b" << std::endl;
    set.remove("b");
    set.print();
    std::cout << "remove d" << std::endl;
    set.remove("d");
    set.print();
    std::cout << "remove c" << std::endl;
    set.remove("c");
    set.print();
    std::cout << "remove q" << std::endl;
    set.remove("q");
    set.print();
    std::cout << "remove r" << std::endl;
    set.remove("r");
    set.print();
    std::cout << "remove a" << std::endl;
    set.remove("a");
    set.print();
    std::cout << "remove " << std::endl;
    set.remove("");
    set.print();
    std::cout << "remove f" << std::endl;
    set.remove("f");
    set.print();
    set.clear();
    set.insert("d");
    set.insert("b");
    set.insert("e");
    set.insert("a");
    set.insert("c");
    set.insert("f");
    set.insert("q");
    set.insert("r");
    set.insert("p");
    set.print();
    Set new_set(set);
    std::cout << "new set:" << std::endl;
    new_set.print();

    return 0;
}
