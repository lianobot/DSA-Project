// Tests for Component 3 (Graph, BFS/DFS). Owner: Member 4.
// Uses plain Student objects - does NOT need the LinkedList, so you can test on your own.
#include "Graph.h"
#include "test_util.h"

namespace {
const int N = 12;
Student g_students[N + 1];            // ids 1..N live at g_students[id]

// Builds a graph with nodes 1..n registered.
void addNodes(Graph& g, int n) {
    for (int i = 1; i <= n; ++i) { g_students[i] = mk(i); g.addNode(&g_students[i]); }
}
}

void test_empty_graph() {
    Graph g(5);
    int n = -1;
    int* r = g.bfs(1, n);
    CHECK(r == nullptr);
    CHECK(n == 0);
    CHECK(g.nodeCount() == 0);
    CHECK(g.edgeCount() == 0);
}

void test_unknown_start_returns_nullptr() {
    Graph g(5);
    addNodes(g, 3);
    int n = -1;
    CHECK(g.bfs(99, n) == nullptr);  CHECK(n == 0);
    n = -1;
    CHECK(g.dfs(99, n) == nullptr);  CHECK(n == 0);
}

void test_isolated_node_reaches_only_itself() {
    Graph g(5);
    addNodes(g, 3);
    g.addEdge(1, 2);                  // node 3 has no friends
    int n = 0;
    int* r = g.bfs(3, n);
    REQUIRE(r != nullptr);
    CHECK(n == 1);
    CHECK(r[0] == 3);
    delete[] r;
    CHECK(g.neighborCount(3) == 0);
}

void test_addNode_rules() {
    Graph g(2);
    Student a = mk(1), b = mk(2), c = mk(3), dup = mk(1);
    CHECK(g.addNode(&a));
    CHECK(!g.addNode(&dup));          // same id
    CHECK(!g.addNode(nullptr));
    CHECK(g.addNode(&b));
    CHECK(!g.addNode(&c));            // capacity (2) reached
    CHECK(g.nodeCount() == 2);
}

void test_addEdge_rules() {
    Graph g(5);
    addNodes(g, 3);
    CHECK(g.addEdge(1, 2));
    CHECK(!g.addEdge(1, 2));          // duplicate
    CHECK(!g.addEdge(2, 1));          // duplicate, other direction
    CHECK(!g.addEdge(3, 3));          // self-loop
    CHECK(!g.addEdge(1, 99));         // unknown id
    CHECK(!g.addEdge(99, 1));
    CHECK(g.edgeCount() == 1);
    CHECK(g.hasEdge(1, 2));
    CHECK(g.hasEdge(2, 1));           // undirected
    CHECK(!g.hasEdge(1, 3));
    CHECK(!g.hasEdge(1, 99));
    CHECK(g.neighborCount(1) == 1);
    CHECK(g.neighborCount(2) == 1);
    CHECK(g.neighborCount(99) == -1);
}

void test_bfs_chain_is_undirected() {
    Graph g(5);
    addNodes(g, 4);
    g.addEdge(1, 2); g.addEdge(2, 3); g.addEdge(3, 4);
    int n = 0;
    int* r = g.bfs(1, n);
    REQUIRE(r != nullptr);
    REQUIRE(n == 4);
    CHECK(r[0] == 1); CHECK(r[1] == 2); CHECK(r[2] == 3); CHECK(r[3] == 4);
    delete[] r;
    r = g.bfs(4, n);                  // walks the same chain backwards because edges go both ways
    REQUIRE(r != nullptr);
    REQUIRE(n == 4);
    CHECK(r[0] == 4); CHECK(r[1] == 3); CHECK(r[2] == 2); CHECK(r[3] == 1);
    delete[] r;
}

void test_bfs_visits_level_by_level() {
    // 1-2, 1-3, 2-4, 3-5  : levels are {1} {2,3} {4,5}
    Graph g(6);
    addNodes(g, 5);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(2, 4); g.addEdge(3, 5);
    int n = 0;
    int* r = g.bfs(1, n);
    REQUIRE(r != nullptr);
    REQUIRE(n == 5);
    CHECK(r[0] == 1);
    CHECK((r[1] == 2 || r[1] == 3) && (r[2] == 2 || r[2] == 3) && r[1] != r[2]);
    CHECK((r[3] == 4 || r[3] == 5) && (r[4] == 4 || r[4] == 5) && r[3] != r[4]);
    delete[] r;
}

void test_bfs_only_reaches_own_component() {
    Graph g(8);
    addNodes(g, 5);
    g.addEdge(1, 2); g.addEdge(2, 3);       // group {1,2,3}
    g.addEdge(4, 5);                        // group {4,5}
    int n = 0;
    int* r = g.bfs(2, n);
    REQUIRE(r != nullptr);
    REQUIRE(n == 3);
    sortInts(r, n);
    CHECK(r[0] == 1); CHECK(r[1] == 2); CHECK(r[2] == 3);
    delete[] r;
}

void test_cycles_do_not_hang_or_repeat() {
    // triangle 1-2-3 plus a square 3-4-5-6-3 : lots of cycles
    Graph g(8);
    addNodes(g, 6);
    g.addEdge(1, 2); g.addEdge(2, 3); g.addEdge(3, 1);
    g.addEdge(3, 4); g.addEdge(4, 5); g.addEdge(5, 6); g.addEdge(6, 3);
    int n = 0;
    int* r = g.bfs(1, n);
    REQUIRE(r != nullptr);
    CHECK(n == 6);
    CHECK(allDistinct(r, n));
    delete[] r;
    r = g.dfs(1, n);
    REQUIRE(r != nullptr);
    CHECK(n == 6);
    CHECK(allDistinct(r, n));
    delete[] r;
}

void test_dfs_same_set_as_bfs() {
    Graph g(N + 1);
    addNodes(g, 10);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(2, 4); g.addEdge(2, 5);
    g.addEdge(3, 6); g.addEdge(6, 7); g.addEdge(8, 9);   // {8,9} and {10} are unreachable from 1
    int nb = 0, nd = 0;
    int* b = g.bfs(1, nb);
    int* d = g.dfs(1, nd);
    REQUIRE(b != nullptr);
    REQUIRE(d != nullptr);
    CHECK(d[0] == 1);
    REQUIRE(nb == nd);
    CHECK(nb == 7);
    sortInts(b, nb); sortInts(d, nd);
    for (int i = 0; i < nb; ++i) CHECK(b[i] == d[i]);
    delete[] b; delete[] d;
}

void test_dfs_goes_deep_first() {
    // chain 1-2-3-4 : DFS from 1 must give 1,2,3,4
    Graph g(5);
    addNodes(g, 4);
    g.addEdge(1, 2); g.addEdge(2, 3); g.addEdge(3, 4);
    int n = 0;
    int* r = g.dfs(1, n);
    REQUIRE(r != nullptr);
    REQUIRE(n == 4);
    CHECK(r[0] == 1); CHECK(r[1] == 2); CHECK(r[2] == 3); CHECK(r[3] == 4);
    delete[] r;
}

// ---- OWNER: add your own tests above this line, then RUN() them below ----

int main() {
    RUN(test_empty_graph);
    RUN(test_unknown_start_returns_nullptr);
    RUN(test_isolated_node_reaches_only_itself);
    RUN(test_addNode_rules);
    RUN(test_addEdge_rules);
    RUN(test_bfs_chain_is_undirected);
    RUN(test_bfs_visits_level_by_level);
    RUN(test_bfs_only_reaches_own_component);
    RUN(test_cycles_do_not_hang_or_repeat);
    RUN(test_dfs_same_set_as_bfs);
    RUN(test_dfs_goes_deep_first);
    return testSummary();
}
