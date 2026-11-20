#include "HashTable.h"

// OWNER: Member 2. STUB - replace each body. Contracts are in HashTable.h.

HashTable::HashTable(int bucketCount) : buckets_(nullptr), bucketCount_(bucketCount < 1 ? 1 : bucketCount), count_(0) {
    // TODO: allocate buckets_ (bucketCount_ chain heads, all nullptr)
}

HashTable::~HashTable() {
    // TODO: delete every chain node, then delete[] buckets_ (do NOT delete the Students)
}

bool HashTable::insert(Student* s) {
    (void)s;
    return false;  // TODO
}

Student* HashTable::find(int id) const {
    (void)id;
    return nullptr;  // TODO
}

int HashTable::size() const {
    return 0;  // TODO
}

int HashTable::bucketOf(int id) const {
    (void)id;
    return 0;  // TODO
}

int HashTable::bucketLength(int b) const {
    (void)b;
    return 0;  // TODO
}
