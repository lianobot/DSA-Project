#pragma once
#include "Record.h"

// COMPONENT 2 - Fast lookup (hash table with separate chaining).   OWNER: Member 2
//
// This is an INDEX: it stores Student* that point into the LinkedList. It never copies a
// Student and never deletes one. The destructor frees only the chain nodes it allocated.
// Bucket for an id = id modulo bucketCount (made non-negative).
class HashTable {
public:
    // bucketCount < 1 is treated as 1.
    explicit HashTable(int bucketCount);
    ~HashTable();                                   // delete every chain node, then the bucket array
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    // Adds s to its bucket. Returns false (and changes nothing) if s is nullptr
    // or a student with the same id is already in the table.
    bool insert(Student* s);

    // Returns the stored pointer for id, or nullptr if absent. Average O(1).
    Student* find(int id) const;

    // Number of students stored in the table.
    int size() const;

    // The bucket index (0 .. bucketCount-1) that id maps to. Used by the collision test.
    int bucketOf(int id) const;

    // How many entries are chained in bucket b (0 if b is out of range). Used by the collision test.
    int bucketLength(int b) const;

private:
    struct Node {
        Student* student;
        Node*    next;
    };
    Node** buckets_;       // array of bucketCount_ chain heads
    int    bucketCount_;
    int    count_;
};
