#pragma once
#include "Record.h"

// COMPONENT 3 - Network & reachability (undirected graph, adjacency lists, BFS/DFS).   OWNER: Member 4
//
// The graph stores Student* (never copies or deletes them). Register every student with
// addNode first, then connect them with addEdge using student IDs.
// Internally each node gets an index 0..nodeCount-1 (= order of addNode); adjacency lists
// store those indices. The graph is UNDIRECTED: addEdge(a,b) makes a<->b.
// Helpers you may use: Queue.h (IntQueue) for BFS, Stack.h (IntStack) for DFS - or recurse.
class Graph {
public:
    // maxNodes = capacity; addNode fails once it is full.
    explicit Graph(int maxNodes);
    ~Graph();                                       // delete every adjacency node, then the arrays
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    // Registers a student. Returns false if s is nullptr, the graph is full,
    // or a node with the same id is already registered.
    bool addNode(Student* s);

    // Adds the friendship idA <-> idB (both directions). Returns false and changes nothing if
    // either id is not registered, idA == idB (self-loop), or the edge already exists
    // (in either direction).
    bool addEdge(int idA, int idB);

    bool hasEdge(int idA, int idB) const;           // false if either id is unknown
    int  nodeCount() const;
    int  edgeCount() const;                         // each friendship counts once

    // Number of friends of id, or -1 if id is not registered.
    int neighborCount(int id) const;

    // Breadth-first search from startId. Returns a NEW int array (caller does delete[]) holding
    // the IDs of every reachable student in visit order; startId is first; each ID appears once.
    // count = length of the array. If startId is unknown: returns nullptr and count = 0.
    // The order in which neighbours are visited is up to you (tests do not depend on it).
    // Must terminate on graphs with cycles (use a visited array).
    int* bfs(int startId, int& count) const;

    // Depth-first search; same contract as bfs (reachable IDs, start first, no repeats).
    int* dfs(int startId, int& count) const;

private:
    struct AdjNode {
        int      to;        // index of the neighbour (NOT its id)
        AdjNode* next;
    };
    int indexOf(int id) const;                      // node index for id, or -1 (linear scan is fine)

    Student** nodes_;       // nodes_[i] = student with index i
    AdjNode** adj_;         // adj_[i]   = head of i's neighbour list
    int       capacity_;
    int       nodeCount_;
    int       edgeCount_;
};
