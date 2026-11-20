// Integration test (handout section 9): load the REAL dataset, then check that all components agree.
#include <fstream>
#include <sstream>
#include "Loader.h"
#include "Ranking.h"
#include "test_util.h"

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif
static std::string path(const char* file) { return std::string(DATA_DIR) + "/" + file; }

namespace {
struct World {
    LinkedList list;
    HashTable  hash;
    Graph      graph;
    LoadReport recReport, edgeReport;
    World() : hash(101), graph(200) {}
    bool load() {
        if (!loadStudents(path("records.csv").c_str(), list, recReport)) return false;
        if (!buildIndex(list, hash)) return false;
        if (!addAllNodes(list, graph)) return false;
        return loadEdges(path("edges.csv").c_str(), list, graph, edgeReport, &hash) && list.size() > 0;
    }
};
}

void test_real_data_loads_cleanly() {
    World w;
    REQUIRE(w.load());
    CHECK(w.recReport.accepted == 40);
    CHECK(w.recReport.rejected == 0);
    CHECK(w.edgeReport.accepted == 47);
    CHECK(w.edgeReport.rejected == 0);
    CHECK(w.list.size() == 40);
    CHECK(w.graph.nodeCount() == 40);
    CHECK(w.graph.edgeCount() == 47);
}

// hash table finds every record the linked list holds, and returns the very same object
void test_hash_agrees_with_list() {
    World w;
    REQUIRE(w.load());
    CHECK(w.hash.size() == w.list.size());
    int checked = 0;
    for (LinkedList::Node* p = w.list.head(); p; p = p->next) {
        CHECK(w.hash.find(p->data.id) == &p->data);
        CHECK(w.list.findById(p->data.id) == &p->data);
        ++checked;
    }
    CHECK(checked == 40);
    CHECK(w.hash.find(999) == nullptr);
    CHECK(w.list.findById(999) == nullptr);
}

void test_degrees_match_graph() {
    World w;
    REQUIRE(w.load());
    int sum = 0;
    for (LinkedList::Node* p = w.list.head(); p; p = p->next) {
        CHECK(p->data.degree == w.graph.neighborCount(p->data.id));
        sum += p->data.degree;
    }
    CHECK(sum == 2 * w.graph.edgeCount());   // handshake lemma
}

// BFS from the starts listed in data/expected_bfs.txt must give exactly the hand-computed reachable sets
void test_bfs_matches_expected_sets() {
    World w;
    REQUIRE(w.load());
    std::ifstream in(path("expected_bfs.txt"));
    REQUIRE(in.good());
    std::string line;
    int cases = 0;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        int start = 0; char colon = 0;
        ss >> start >> colon;
        int expected[100]; int ne = 0, v;
        while (ss >> v && ne < 100) expected[ne++] = v;

        int n = 0;
        int* got = w.graph.bfs(start, n);
        REQUIRE(got != nullptr);
        CHECK(got[0] == start);
        CHECK(n == ne);
        if (n == ne) {
            sortInts(got, n);
            for (int i = 0; i < n; ++i) CHECK(got[i] == expected[i]);
        }
        delete[] got;

        int nd = 0;                           // DFS reaches the same set
        int* d = w.graph.dfs(start, nd);
        REQUIRE(d != nullptr);
        CHECK(nd == ne);
        delete[] d;
        ++cases;
    }
    CHECK(cases >= 4);
}

// the ranking must match data/expected_ranking.txt position by position
void test_ranking_matches_expected() {
    World w;
    REQUIRE(w.load());
    int count = 0;
    Student** r = rankByDegree(w.list, count);
    REQUIRE(r != nullptr);
    REQUIRE(count == 40);
    std::ifstream in(path("expected_ranking.txt"));
    REQUIRE(in.good());
    std::string line;
    int pos = 0;
    while (std::getline(in, line) && pos < count) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        int id = 0, deg = 0;
        ss >> id >> deg;
        CHECK(r[pos]->id == id);
        CHECK(r[pos]->degree == deg);
        ++pos;
    }
    CHECK(pos == 40);
    REQUIRE(w.list.at(0) != nullptr);
    CHECK(w.list.at(0)->id == 101);           // list itself was not reordered
    delete[] r;
}

int main() {
    RUN(test_real_data_loads_cleanly);
    RUN(test_hash_agrees_with_list);
    RUN(test_degrees_match_graph);
    RUN(test_bfs_matches_expected_sets);
    RUN(test_ranking_matches_expected);
    return testSummary();
}
