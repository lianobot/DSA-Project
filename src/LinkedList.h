#pragma once
#include "Record.h"

// COMPONENT 1 - Record storage (singly linked list).   OWNER: Member 1 (team lead)
//
// The list OWNS every Student it stores. Each Student lives inside a heap-allocated Node and
// NEVER MOVES, so a Student* returned by this class stays valid until the list is destroyed.
// (The hash table and the graph rely on that.)
class LinkedList {
public:
    struct Node {
        Student data;
        Node*   next;
    };

    LinkedList();
    ~LinkedList();                                  // must delete every node
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Appends a copy of s at the TAIL (insertion order is preserved).
    // Returns false and changes nothing if a student with s.id is already stored.
    bool insert(const Student& s);

    // Same as insert but WITHOUT the duplicate check (O(1) instead of O(n)).
    // Only for the timing benchmark, which must build 100,000 records quickly.
    // Returns a pointer to the stored copy.
    Student* insertUnchecked(const Student& s);

    // Linear scan. Returns the stored Student, or nullptr if id is not present.
    Student* findById(int id) const;

    // Number of stored students.
    int size() const;

    // index 0 = first inserted. Returns nullptr if index < 0 or index >= size(). O(n).
    Student* at(int index) const;

    // First node (nullptr if empty); follow ->next to iterate in O(n) total.
    Node* head() const;

private:
    Node* head_;
    Node* tail_;
    int   count_;
};
