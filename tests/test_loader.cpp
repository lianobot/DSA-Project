// Tests for the Loader and its validation rules (team lead). Needs LinkedList, HashTable and Graph to work.
#include "Loader.h"
#include "test_util.h"

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif
static std::string path(const char* file) { return std::string(DATA_DIR) + "/" + file; }

void test_load_good_records() {
    LinkedList l;
    LoadReport r;
    REQUIRE(loadStudents(path("fake_small_records.csv").c_str(), l, r));
    CHECK(r.accepted == 5);
    CHECK(r.rejected == 0);
    CHECK(l.size() == 5);
    Student* p = l.findById(3);
    REQUIRE(p != nullptr);
    CHECK(p->name == "Carol");
    CHECK(p->batch == 2024);
    CHECK(p->club == "Music");
    CHECK(p->degree == 0);
}

void test_empty_dataset() {
    LinkedList l;
    LoadReport r;
    CHECK(loadStudents(path("empty_records.csv").c_str(), l, r));
    CHECK(r.accepted == 0);
    CHECK(r.rejected == 0);
    CHECK(l.size() == 0);
}

void test_missing_file_reports_failure() {
    LinkedList l;
    LoadReport r;
    CHECK(!loadStudents(path("does_not_exist.csv").c_str(), l, r));
    CHECK(l.size() == 0);
}

// duplicate ID rejected, malformed rows rejected (bad_records.csv: 3 good, 1 duplicate, 1 bad id, 1 short row)
void test_duplicate_and_malformed_records_rejected() {
    LinkedList l;
    LoadReport r;
    REQUIRE(loadStudents(path("bad_records.csv").c_str(), l, r));
    CHECK(r.accepted == 3);
    CHECK(r.rejected == 3);
    CHECK(l.size() == 3);
    Student* p = l.findById(2);
    REQUIRE(p != nullptr);
    CHECK(p->name == "Bob");                 // the first row with id 2 wins
}

void test_good_edges_set_degrees() {
    LinkedList l;
    LoadReport rr, er;
    REQUIRE(loadStudents(path("fake_small_records.csv").c_str(), l, rr));
    Graph g(l.size());
    REQUIRE(addAllNodes(l, g));
    REQUIRE(loadEdges(path("fake_small_edges.csv").c_str(), l, g, er));
    CHECK(er.accepted == 4);
    CHECK(er.rejected == 0);
    CHECK(g.edgeCount() == 4);
    Student *s1 = l.findById(1), *s3 = l.findById(3), *s4 = l.findById(4), *s5 = l.findById(5);
    REQUIRE(s1 && s3 && s4 && s5);
    CHECK(s1->degree == 2);                  // 1-2, 1-3
    CHECK(s3->degree == 3);                  // 1-3, 2-3, 3-4
    CHECK(s4->degree == 1);
    CHECK(s5->degree == 0);                  // Eve has no friends
}

// unknown ID, self-loop, duplicate (both directions), malformed -> all rejected; 3 good edges kept
void test_bad_edges_rejected() {
    LinkedList l;
    for (int i = 1; i <= 4; ++i) l.insert(mk(i));
    Graph g(4);
    REQUIRE(addAllNodes(l, g));
    LoadReport er;
    REQUIRE(loadEdges(path("bad_edges.csv").c_str(), l, g, er));
    CHECK(er.accepted == 3);                 // 1-2, 2-3, 3-4
    CHECK(er.rejected == 6);                 // 2 unknown, 1 self-loop, 2 duplicates, 1 malformed
    CHECK(g.edgeCount() == 3);
    Student *s1 = l.findById(1), *s2 = l.findById(2), *s3 = l.findById(3);
    REQUIRE(s1 && s2 && s3);
    CHECK(s2->degree == 2);
    CHECK(s3->degree == 2);
    CHECK(s1->degree == 1);                  // the rejected duplicates did NOT add degree
}

void test_edges_with_hash_index_give_same_result() {
    LinkedList l;
    LoadReport rr, er;
    REQUIRE(loadStudents(path("fake_small_records.csv").c_str(), l, rr));
    HashTable h(7);
    REQUIRE(buildIndex(l, h));
    Graph g(l.size());
    REQUIRE(addAllNodes(l, g));
    REQUIRE(loadEdges(path("fake_small_edges.csv").c_str(), l, g, er, &h));
    CHECK(er.accepted == 4);
    Student* s3 = l.findById(3);
    REQUIRE(s3 != nullptr);
    CHECK(s3->degree == 3);
}

// ---- add more tests above this line, then RUN() them below ----

int main() {
    RUN(test_load_good_records);
    RUN(test_empty_dataset);
    RUN(test_missing_file_reports_failure);
    RUN(test_duplicate_and_malformed_records_rejected);
    RUN(test_good_edges_set_degrees);
    RUN(test_bad_edges_rejected);
    RUN(test_edges_with_hash_index_give_same_result);
    return testSummary();
}
