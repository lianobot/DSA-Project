#include "LinkedList.h"

// OWNER: Member 1. STUB - replace each body. Contracts are in LinkedList.h.

LinkedList::LinkedList() : head_(nullptr), tail_(nullptr), count_(0) {}

LinkedList::~LinkedList() {
    // TODO: delete every node
}

bool LinkedList::insert(const Student& s) {
    (void)s;
    return false;  // TODO
}

Student* LinkedList::insertUnchecked(const Student& s) {
    (void)s;
    return nullptr;  // TODO
}

Student* LinkedList::findById(int id) const {
    (void)id;
    return nullptr;  // TODO
}

int LinkedList::size() const {
    return 0;  // TODO
}

Student* LinkedList::at(int index) const {
    (void)index;
    return nullptr;  // TODO
}

LinkedList::Node* LinkedList::head() const {
    return nullptr;  // TODO
}
