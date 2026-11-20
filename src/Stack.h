#pragma once
// Header-only helper for Component 3 (iterative DFS). Linked-node stack of ints. No STL.
// pop() on an empty stack returns -1 (check empty() first).
class IntStack {
public:
    IntStack() : top_(nullptr), size_(0) {}
    ~IntStack() { while (!empty()) pop(); }
    IntStack(const IntStack&) = delete;
    IntStack& operator=(const IntStack&) = delete;

    void push(int v) { top_ = new Node{v, top_}; ++size_; }
    int pop() {
        if (!top_) return -1;
        Node* n = top_;
        int v = n->value;
        top_ = n->next;
        delete n;
        --size_;
        return v;
    }
    bool empty() const { return size_ == 0; }
    int  size()  const { return size_; }

private:
    struct Node { int value; Node* next; };
    Node* top_;
    int   size_;
};
