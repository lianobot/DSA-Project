// Tests for Component 4 (Ranking, merge sort). Owner: Member 3.
// The mergeSortByDegree tests use plain Student objects - they do NOT need the LinkedList.
// Only the last two tests (rankByDegree) need a working LinkedList.
#include "Ranking.h"
#include "test_util.h"

namespace {
// true if a[0..n-1] is degree-descending with ties by id ascending
bool isRanked(Student** a, int n) {
    for (int i = 0; i + 1 < n; ++i) {
        if (a[i]->degree < a[i + 1]->degree) return false;
        if (a[i]->degree == a[i + 1]->degree && a[i]->id > a[i + 1]->id) return false;
    }
    return true;
}
}

void test_sort_known_five() {
    // ids 10..50 with degrees 3,1,3,0,2  ->  expected order: 10(3) 30(3) 50(2) 20(1) 40(0)
    Student s[5] = { mk(10, "a", 2025, "c", 3), mk(20, "b", 2025, "c", 1), mk(30, "c", 2025, "c", 3),
                     mk(40, "d", 2025, "c", 0), mk(50, "e", 2025, "c", 2) };
    Student* p[5] = { &s[0], &s[1], &s[2], &s[3], &s[4] };
    mergeSortByDegree(p, 5);
    CHECK(p[0]->id == 10); CHECK(p[1]->id == 30); CHECK(p[2]->id == 50);
    CHECK(p[3]->id == 20); CHECK(p[4]->id == 40);
}

void test_sort_empty_and_single() {
    mergeSortByDegree(nullptr, 0);             // must not crash
    Student a = mk(1, "a", 2025, "c", 4);
    Student* p[1] = { &a };
    mergeSortByDegree(p, 1);
    CHECK(p[0] == &a);
}

void test_sort_ties_broken_by_id() {
    Student s[6];
    Student* p[6];
    int ids[6] = { 60, 20, 50, 10, 40, 30 };   // all the same degree
    for (int i = 0; i < 6; ++i) { s[i] = mk(ids[i], "x", 2025, "c", 2); p[i] = &s[i]; }
    mergeSortByDegree(p, 6);
    for (int i = 0; i < 6; ++i) CHECK(p[i]->id == (i + 1) * 10);
}

void test_sort_already_sorted_and_reversed() {
    Student s[8];
    Student* asc[8];
    Student* desc[8];
    for (int i = 0; i < 8; ++i) { s[i] = mk(i + 1, "x", 2025, "c", 8 - i); asc[i] = &s[i]; desc[7 - i] = &s[i]; }
    mergeSortByDegree(asc, 8);                  // already in final order
    mergeSortByDegree(desc, 8);                 // exactly reversed
    CHECK(isRanked(asc, 8));
    CHECK(isRanked(desc, 8));
    CHECK(asc[0]->id == 1 && desc[0]->id == 1);
}

void test_sort_odd_size_and_pointers_not_copies() {
    Student s[7];
    Student* p[7];
    int deg[7] = { 2, 5, 1, 5, 0, 3, 2 };
    for (int i = 0; i < 7; ++i) { s[i] = mk(i + 1, "x", 2025, "c", deg[i]); p[i] = &s[i]; }
    mergeSortByDegree(p, 7);
    CHECK(isRanked(p, 7));
    for (int i = 0; i < 7; ++i) {               // every original object still appears exactly once
        int found = 0;
        for (int j = 0; j < 7; ++j) if (p[j] == &s[i]) ++found;
        CHECK(found == 1);
    }
}

void test_sort_larger_pseudorandom() {
    const int N = 200;
    static Student s[N];
    static Student* p[N];
    unsigned x = 12345;
    for (int i = 0; i < N; ++i) {
        x = x * 1103515245u + 12345u;
        s[i] = mk(i + 1, "x", 2025, "c", (int)((x >> 16) % 10));
        p[i] = &s[i];
    }
    mergeSortByDegree(p, N);
    CHECK(isRanked(p, N));
}

void test_rank_empty_list() {
    LinkedList l;
    int count = -1;
    Student** r = rankByDegree(l, count);
    CHECK(r == nullptr);
    CHECK(count == 0);
}

void test_rank_from_list_does_not_reorder_list() {
    LinkedList l;
    l.insert(mk(1, "a", 2025, "c", 1));
    l.insert(mk(2, "b", 2025, "c", 4));
    l.insert(mk(3, "c", 2025, "c", 4));
    l.insert(mk(4, "d", 2025, "c", 0));
    int count = 0;
    Student** r = rankByDegree(l, count);
    REQUIRE(r != nullptr);
    REQUIRE(count == 4);
    CHECK(r[0]->id == 2); CHECK(r[1]->id == 3); CHECK(r[2]->id == 1); CHECK(r[3]->id == 4);
    CHECK(r[0] == l.findById(2));              // points at the list's students, not copies
    CHECK(l.at(0) != nullptr && l.at(0)->id == 1);   // list order unchanged
    CHECK(l.at(1) != nullptr && l.at(1)->id == 2);
    delete[] r;
}

// ---- OWNER: add your own tests above this line, then RUN() them below ----

int main() {
    RUN(test_sort_known_five);
    RUN(test_sort_empty_and_single);
    RUN(test_sort_ties_broken_by_id);
    RUN(test_sort_already_sorted_and_reversed);
    RUN(test_sort_odd_size_and_pointers_not_copies);
    RUN(test_sort_larger_pseudorandom);
    RUN(test_rank_empty_list);
    RUN(test_rank_from_list_does_not_reorder_list);
    return testSummary();
}
