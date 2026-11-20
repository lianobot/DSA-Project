#pragma once
// Header-only helper for Component 3 (BFS). Linked-node queue of ints. No STL.
// Written by the team lead; Graph.cpp may use it. pop() on an empty queue returns -1 (check empty() first).
class IntQueue {
public:
    IntQueue() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~IntQueue() { while (!empty()) pop(); }
    IntQueue(const IntQueue&) = delete;
    IntQueue& operator=(const IntQueue&) = delete;

    void push(int v) {
        Node* n = new Node{v, nullptr};
        if (tail_) tail_->next = n; else head_ = n;
        tail_ = n;
        ++size_;
    }
    int pop() {
        if (!head_) return -1;
        Node* n = head_;
        int v = n->value;
        head_ = n->next;
        if (!head_) tail_ = nullptr;
        delete n;
        --size_;
        return v;
    }
    bool empty() const { return size_ == 0; }
    int  size()  const { return size_; }

private:
    struct Node { int value; Node* next; };
    Node* head_;
    Node* tail_;
    int   size_;
};
