#include "Graph.h"
#include "Queue.h"   // IntQueue for BFS
#include "Stack.h"   // IntStack for DFS (optional)

// OWNER: Member 4. STUB - replace each body. Contracts are in Graph.h.

Graph::Graph(int maxNodes)
    : nodes_(nullptr), adj_(nullptr), capacity_(maxNodes < 0 ? 0 : maxNodes), nodeCount_(0), edgeCount_(0) {
    // TODO: allocate nodes_ and adj_ (capacity_ entries each, adj_ all nullptr)
}

Graph::~Graph() {
    // TODO: delete every AdjNode in every list, then delete[] adj_ and nodes_ (NOT the Students)
}

bool Graph::addNode(Student* s) {
    (void)s;
    return false;  // TODO
}

bool Graph::addEdge(int idA, int idB) {
    (void)idA; (void)idB;
    return false;  // TODO
}

bool Graph::hasEdge(int idA, int idB) const {
    (void)idA; (void)idB;
    return false;  // TODO
}

int Graph::nodeCount() const {
    return 0;  // TODO
}

int Graph::edgeCount() const {
    return 0;  // TODO
}

int Graph::neighborCount(int id) const {
    (void)id;
    return -1;  // TODO
}

int* Graph::bfs(int startId, int& count) const {
    (void)startId;
    count = 0;
    return nullptr;  // TODO
}

int* Graph::dfs(int startId, int& count) const {
    (void)startId;
    count = 0;
    return nullptr;  // TODO
}

int Graph::indexOf(int id) const {
    (void)id;
    return -1;  // TODO
}
