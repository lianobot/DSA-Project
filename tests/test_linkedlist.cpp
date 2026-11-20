// Tests for Component 1 (LinkedList). Owner: Member 1.
#include "LinkedList.h"
#include "test_util.h"

void test_empty_list() {
    LinkedList l;
    CHECK(l.size() == 0);
    CHECK(l.findById(1) == nullptr);
    CHECK(l.at(0) == nullptr);
    CHECK(l.head() == nullptr);
}

void test_single_record() {
    LinkedList l;
    REQUIRE(l.insert(mk(7, "Alice", 2025, "Music")));
    CHECK(l.size() == 1);
    Student* p = l.findById(7);
    REQUIRE(p != nullptr);
    CHECK(p->id == 7);
    CHECK(p->name == "Alice");
    CHECK(p->batch == 2025);
    CHECK(p->club == "Music");
    CHECK(l.at(0) == p);
}

void test_insert_and_find_many() {
    LinkedList l;
    for (int i = 1; i <= 10; ++i) CHECK(l.insert(mk(i * 10)));
    CHECK(l.size() == 10);
    for (int i = 1; i <= 10; ++i) {
        Student* p = l.findById(i * 10);
        REQUIRE(p != nullptr);
        CHECK(p->id == i * 10);
    }
}

void test_find_missing_id() {
    LinkedList l;
    l.insert(mk(1));
    l.insert(mk(2));
    CHECK(l.findById(3) == nullptr);
    CHECK(l.findById(0) == nullptr);
    CHECK(l.findById(-5) == nullptr);
}

void test_duplicate_id_rejected() {
    LinkedList l;
    REQUIRE(l.insert(mk(5, "First")));
    CHECK(!l.insert(mk(5, "Second")));
    CHECK(l.size() == 1);
    Student* p = l.findById(5);
    REQUIRE(p != nullptr);
    CHECK(p->name == "First");   // original untouched
}

void test_insertion_order_and_at() {
    LinkedList l;
    l.insert(mk(30)); l.insert(mk(10)); l.insert(mk(20));
    REQUIRE(l.at(0) != nullptr && l.at(1) != nullptr && l.at(2) != nullptr);
    CHECK(l.at(0)->id == 30);
    CHECK(l.at(1)->id == 10);
    CHECK(l.at(2)->id == 20);
    CHECK(l.at(3) == nullptr);
    CHECK(l.at(-1) == nullptr);
}

void test_head_iteration() {
    LinkedList l;
    for (int i = 1; i <= 5; ++i) l.insert(mk(i));
    int n = 0;
    for (LinkedList::Node* p = l.head(); p; p = p->next) { ++n; CHECK(p->data.id == n); }
    CHECK(n == 5);
}

// The hash table and graph keep Student* - the addresses must never change after later inserts.
void test_pointers_stay_valid_after_more_inserts() {
    LinkedList l;
    l.insert(mk(1, "Stable"));
    Student* first = l.findById(1);
    REQUIRE(first != nullptr);
    for (int i = 2; i <= 500; ++i) l.insert(mk(i));
    CHECK(l.findById(1) == first);
    CHECK(first->name == "Stable");
}

void test_insert_unchecked_returns_pointer() {
    LinkedList l;
    Student* p = l.insertUnchecked(mk(9, "X"));
    REQUIRE(p != nullptr);
    CHECK(p->id == 9);
    CHECK(l.size() == 1);
    CHECK(l.findById(9) == p);
}

// ---- OWNER: add your own tests above this line, then RUN() them below ----

int main() {
    RUN(test_empty_list);
    RUN(test_single_record);
    RUN(test_insert_and_find_many);
    RUN(test_find_missing_id);
    RUN(test_duplicate_id_rejected);
    RUN(test_insertion_order_and_at);
    RUN(test_head_iteration);
    RUN(test_pointers_stay_valid_after_more_inserts);
    RUN(test_insert_unchecked_returns_pointer);
    return testSummary();
}
