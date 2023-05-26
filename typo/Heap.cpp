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
    if (mCount == 0) {
        throw std::underflow_error("heap is empty");
    }
    if (mCount == 1) {
        mCount--;
        return mData[0];
    }
    Entry min_entry = mData[0]; // make a copy of the entry to return
    mCount--; // decrement count
    mData[0] = mData[mCount]; // put last entry in index 0
    size_t i = 0; // i = index of parent
    while (i < mCount) {
        if ((i * 2 + 2) >= mCount) {
            if ((i * 2 + 1) >= mCount) { // no children
                break;
            }
            if (mData[i * 2 + 1].score < mData[i].score) {
                Entry temp_child = mData[i * 2 + 1];
                mData[i * 2 + 1] = mData[i];
                mData[i] = temp_child;
                i = i * 2 + 1;
            }
            else {
                break;
            }
        }
        else { // both children
            float curr_score = mData[i].score;
            float left_child_score = mData[i * 2 + 1].score;
            float right_child_score = mData[i * 2 + 2].score;
            if (left_child_score >= curr_score && right_child_score >= curr_score) {
                break;
            }
            else if (left_child_score >= curr_score) {
                Entry temp_child = mData[i * 2 + 2];
                mData[i * 2 + 2] = mData[i];
                mData[i] = temp_child;
                i = i * 2 + 2;
            }
            else if (right_child_score >= curr_score) {
                Entry temp_child = mData[i * 2 + 1];
                mData[i * 2 + 1] = mData[i];
                mData[i] = temp_child;
                i = i * 2 + 1;
            }
            else {
                if (left_child_score <= right_child_score) {
                    Entry temp_child = mData[i * 2 + 1];
                    mData[i * 2 + 1] = mData[i];
                    mData[i] = temp_child;
                    i = i * 2 + 1;
                }
                else {
                    Entry temp_child = mData[i * 2 + 2];
                    mData[i * 2 + 2] = mData[i];
                    mData[i] = temp_child;
                    i = i * 2 + 2;
                }
            }
        }
    }
    return min_entry;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        throw std::underflow_error("heap is empty");
    }
    if (mCount == 1) {
        Entry min_entry = mData[0]; // make a copy of the entry to return
        mData[0].value = value;
        mData[0].score = score;
        return min_entry;
    }
    Entry min_entry = mData[0]; // make a copy of the entry to return
    mData[0].value = value;
    mData[0].score = score;
    size_t i = 0; // i = index of parent
    while (i < mCount) {
        if ((i * 2 + 2) >= mCount) {
            if ((i * 2 + 1) >= mCount) { // no children
                break;
            }
            if (mData[i * 2 + 1].score < mData[i].score) {
                Entry temp_child = mData[i * 2 + 1];
                mData[i * 2 + 1] = mData[i];
                mData[i] = temp_child;
                i = i * 2 + 1;
            }
            else {
                break;
            }
        }
        else { // both children
            float curr_score = mData[i].score;
            float left_child_score = mData[i * 2 + 1].score;
            float right_child_score = mData[i * 2 + 2].score;
            if (left_child_score >= curr_score && right_child_score >= curr_score) {
                break;
            }
            else if (left_child_score >= curr_score) {
                Entry temp_child = mData[i * 2 + 2];
                mData[i * 2 + 2] = mData[i];
                mData[i] = temp_child;
                i = i * 2 + 2;
            }
            else if (right_child_score >= curr_score) {
                Entry temp_child = mData[i * 2 + 1];
                mData[i * 2 + 1] = mData[i];
                mData[i] = temp_child;
                i = i * 2 + 1;
            }
            else {
                if (left_child_score <= right_child_score) {
                    Entry temp_child = mData[i * 2 + 1];
                    mData[i * 2 + 1] = mData[i];
                    mData[i] = temp_child;
                    i = i * 2 + 1;
                }
                else {
                    Entry temp_child = mData[i * 2 + 2];
                    mData[i * 2 + 2] = mData[i];
                    mData[i] = temp_child;
                    i = i * 2 + 2;
                }
            }
        }
    }
    return min_entry;
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("heap is full");
    }
    if (mCount == 0) {
        mData[0].value = value;
        mData[0].score = score;
        mCount++;
        return;
    }
    mData[mCount].value = value;
    mData[mCount].score = score;
    size_t i = mCount;
    Entry new_entry = mData[i];
    Entry parent_entry = mData[(i - 1) / 2];
    while (i != 0 && parent_entry.score > new_entry.score) {
        mData[i] = parent_entry;
        i = (i - 1) / 2;
        mData[i] = new_entry;
        if (i > 0) {
            parent_entry = mData[(i - 1) / 2];
        }
    }
    mCount++;
    return;
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("heap is empty");
    }
    return mData[0];
}
