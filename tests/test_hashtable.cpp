// Tests for Component 2 (HashTable). Owner: Member 2.
// Uses plain Student objects - does NOT need the LinkedList, so you can test on your own.
#include "HashTable.h"
#include "test_util.h"

void test_empty_table() {
    HashTable h(11);
    CHECK(h.size() == 0);
    CHECK(h.find(1) == nullptr);
}

void test_insert_and_find() {
    Student s[20];
    HashTable h(11);
    for (int i = 0; i < 20; ++i) { s[i] = mk(100 + i); CHECK(h.insert(&s[i])); }
    CHECK(h.size() == 20);
    for (int i = 0; i < 20; ++i) CHECK(h.find(100 + i) == &s[i]);   // same pointer, not a copy
}

void test_missing_id_returns_nullptr() {
    Student a = mk(1), b = mk(2);
    HashTable h(11);
    h.insert(&a); h.insert(&b);
    CHECK(h.find(3) == nullptr);
    CHECK(h.find(0) == nullptr);
    CHECK(h.find(12) == nullptr);   // same bucket as 1 (mod 11) but not stored
}

void test_duplicate_id_rejected() {
    Student a = mk(5, "First"), b = mk(5, "Second");
    HashTable h(11);
    REQUIRE(h.insert(&a));
    CHECK(!h.insert(&b));
    CHECK(h.size() == 1);
    CHECK(h.find(5) == &a);
}

void test_null_insert_rejected() {
    HashTable h(11);
    CHECK(!h.insert(nullptr));
    CHECK(h.size() == 0);
}

// EDGE CASE required by the handout: a collision is forced on purpose and handled correctly.
void test_forced_collision_is_handled() {
    Student a = mk(5), b = mk(16), c = mk(27);       // 5, 16, 27 are all = 5 (mod 11)
    HashTable h(11);
    REQUIRE(h.insert(&a));
    REQUIRE(h.insert(&b));
    REQUIRE(h.insert(&c));
    CHECK(h.bucketOf(5) == h.bucketOf(16));
    CHECK(h.bucketOf(16) == h.bucketOf(27));
    CHECK(h.bucketLength(h.bucketOf(5)) == 3);        // all three share one chain
    CHECK(h.find(5)  == &a);
    CHECK(h.find(16) == &b);
    CHECK(h.find(27) == &c);
    CHECK(h.find(38) == nullptr);                     // same bucket, not stored
    CHECK(h.size() == 3);
}

void test_single_bucket_table_still_works() {
    Student s[10];
    HashTable h(1);                                    // everything collides
    for (int i = 0; i < 10; ++i) { s[i] = mk(i + 1); CHECK(h.insert(&s[i])); }
    CHECK(h.bucketLength(0) == 10);
    for (int i = 0; i < 10; ++i) CHECK(h.find(i + 1) == &s[i]);
}

void test_bucketOf_stays_in_range() {
    HashTable h(7);
    for (int id = 1; id <= 100; ++id) {
        int b = h.bucketOf(id);
        CHECK(b >= 0 && b < 7);
    }
}

// ---- OWNER: add your own tests above this line, then RUN() them below ----

int main() {
    RUN(test_empty_table);
    RUN(test_insert_and_find);
    RUN(test_missing_id_returns_nullptr);
    RUN(test_duplicate_id_rejected);
    RUN(test_null_insert_rejected);
    RUN(test_forced_collision_is_handled);
    RUN(test_single_bucket_table_still_works);
    RUN(test_bucketOf_stays_in_range);
    return testSummary();
}
