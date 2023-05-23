#include "Heap.h"

Heap::Heap(size_t capacity) {
    mCapacity = capacity;
    mCount = 0;
    if (mCapacity == 0) {
        mData = nullptr;
    }
    else {
        mData = new Entry[mCapacity];
    }
}

Heap::Heap(const Heap& other) {
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    if (mCapacity == 0) {
        mData = nullptr;
    }
    else {
        mData = new Entry[mCapacity];
        for (size_t i = 0; i < mCapacity; i++) {
            mData[i] = other.mData[i];
        }
    }
}

Heap::Heap(Heap&& other) {
    mData = other.mData;
    other.mData = nullptr;
}

Heap::~Heap() {
    delete [] mData;
    mCount = 0;
    mCapacity = 0;
    mData = nullptr;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Entry& lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("index out of range");
    }
    return mData[index];
}

Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("no items in heap");
    }
    Entry popped = *mData[0];
    delete mData[0];
    mData[0] = mData[mCount - 1];
    delete mData[mCount - 1];
    size_t curr_index = 0;
    size_t lc_index = curr_index * 2 + 1;
    size_t rc_index = curr_index * 2 + 2;
    Entry* curr = mData[curr_index];
    Entry* lc = mData[lc_index];
    Entry* rc = mData[rc_index];
    while (lc->score < curr->score || rc->score < curr->score) {
        if (lc->score <= rc->score) {
            Entry* temp = lc;
            mData[lc_index] = curr;
            mData[curr_index] = temp;
            curr_index = lc_index;
            lc_index = curr_index * 2 + 1;
            rc_index = curr_index * 2 + 2;
            curr = mData[curr_index];
            lc = mData[lc_index];
            rc = mData[rc_index];
        }
        else {
            Entry* temp = rc;
            mData[rc_index] = curr;
            mData[curr_index] = temp;
            curr_index = rc_index;
            lc_index = curr_index * 2 + 1;
            rc_index = curr_index * 2 + 2;
            curr = mData[curr_index];
            lc = mData[lc_index];
            rc = mData[rc_index];
        }
    }
}

Entry Heap::pushpop(const std::string& value, float score) {
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("heap is full");
    }
    Entry* new_entry = new Entry;
    new_entry->value = value;
    new_entry->score = score;
    mData[mCount] = new_entry;
    if (mCount == 0) {
        mCount++;
        return;
    }
    size_t parent_index = (mCount - 1) / 2;
    size_t new_index = mCount;
    Entry* parent = mData[parent_index];
    while (parent->score > new_entry->score || new_index > 0) {
        Entry* temp = parent;
        mData[parent_index] = new_entry;
        mData[new_index] = temp;
        parent = temp;
        new_index = parent_index;
        parent_index = (new_index - 1) / 2;
    }
    mCount++;
}

const Heap::Entry& top() const {
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
