#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>

#include "DataStore.h"

// This is the Counter class you need to implement.
// It includes the Counter::Iterator as a nested class.
// If you want more space to implement helper classes,
// you can use the DataStore.* and Index.* files.

class Counter {
public:
  class Iterator {
    // Member Variables
    Node* current_node = nullptr;
    //static Node* fake;
    Node* fake;

  public:
    Iterator(Node* head, bool end = false);
    ~Iterator();
    const std::string& key() const;
    int value() const;

    Iterator& operator ++ ();
    bool      operator == (const Iterator& other) const;
    bool      operator != (const Iterator& other) const;
  };

private:
  // Member Variables
  int num_keys = 0;
  int sum_counts = 0;
  DataStore list;

private:
  // Helper Functions

public:
  Counter();
  ~Counter();

  size_t count() const;
  int    total() const;

  void inc(const std::string& key, int by = 1);
  void dec(const std::string& key, int by = 1);
  void del(const std::string& key);
  int  get(const std::string& key) const;
  void set(const std::string& key, int count);

  Iterator begin() const;
  Iterator end() const;
};

#endif
