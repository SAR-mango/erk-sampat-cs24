#include "Heap.h"
#include <stdexcept>
#include <iostream>

Heap::Heap(size_t capacity) {
    if (capacity > 0) {
        mCapacity = capacity;
        mData = new Entry[capacity];
        mCount = 0;
    }
    else {
        mCapacity = 0;
        mData = nullptr;
        mCount = 0;
    }
}

Heap::Heap(const Heap& other) {
    if (other.mCapacity > 0) {
        mCapacity = other.mCapacity;
        mData = new Entry[mCapacity];
        mCount = other.mCount;
        for (size_t i = 0; i < mCount; i++) {
            mData[i] = other.mData[i];
        }
    }
    else {
        mCapacity = 0;
        mData = nullptr;
        mCount = 0;
    }
}

Heap::Heap(Heap&& other) {
    mCapacity = other.mCapacity;
    other.mCapacity = 0;
    mData = other.mData;
    other.mData = nullptr;
    mCount = other.mCount;
    other.mCount = 0;
}

Heap::~Heap() {
    mCapacity = 0;
    delete [] mData;
    mData = nullptr;
    mCount = 0;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("index out of range");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    return mData[0];
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    return mData[0];
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("heap is full");
    }
    if (mCount == 0) {
        //std::cout << "nothing in heap, so putting " << value << " in index 0" << std::endl;
        mData[0].value = value;
        mData[0].score = score;
        mCount++;
        return;
    }
    mData[mCount].value = value;
    mData[mCount].score = score; // put new entry in first available slot
    //std::cout << "heap not empty, so putting " << value << " in index " << mCount << std::endl;
    size_t i = mCount; // index of new entry
    Entry new_entry = mData[i]; // save a copy of new entry
    Entry parent_entry = mData[(i - 1) / 2]; // save a copy of its parent
    while (i != 0 && parent_entry.score > new_entry.score) { // if new entry is at the beginning or its score is higher than its parent's score, we are done; otherwise, swap the new entry with its parent
        //std::cout << "swapping" << std::endl;
        mData[i] = parent_entry; // replace new entry with its parent
        i = (i - 1) / 2; // index of new entry is now index of its parent
        mData[i] = new_entry; // replace parent with new entry
        if (i > 0) {
            parent_entry = mData[(i - 1) / 2]; // set the new parent, but only if the new entry is not at the beginning
        }
    }
    mCount++;
    for (size_t i = 0; i < mCount; i++) {
        //std::cout << '[' << mData[i].value << ", " << mData[i].score << "] ";
    }
    //std::cout << std::endl;
    return;
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("heap is empty");
    }
    return mData[0];
}

/*class Heap {
public:
    struct Entry {
        std::string value;
        float       score;
    };

private:
    Entry* mData;
    size_t mCapacity;
    size_t mCount;

public:
    Heap(size_t capacity);
    Heap(const Heap& other);
    Heap(Heap&& other);
    ~Heap();

    size_t       capacity() const;
    size_t       count() const;
    const Entry& lookup(size_t index) const;
    Entry        pop();
    Entry        pushpop(const std::string& value, float score);
    void         push(const std::string& value, float score);
    const Entry& top() const;
};*/
