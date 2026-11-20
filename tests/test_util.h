#pragma once
// Tiny test helpers (no external framework). Each test file has its own main().
#include <iostream>
#include <string>
#include "Record.h"

inline bool g_ok   = true;
inline int  g_pass = 0;
inline int  g_fail = 0;

// CHECK: records a failure but keeps running the test.
#define CHECK(cond) do { if (!(cond)) { std::cout << "    CHECK failed: " #cond " (line " << __LINE__ << ")\n"; g_ok = false; } } while (0)
// REQUIRE: records a failure and leaves the test at once (use before dereferencing a pointer).
// Only usable inside a void test function.
#define REQUIRE(cond) do { if (!(cond)) { std::cout << "    REQUIRE failed: " #cond " (line " << __LINE__ << ")\n"; g_ok = false; return; } } while (0)

typedef void (*TestFn)();
inline void runTest(const char* name, TestFn fn) {
    g_ok = true;
    fn();
    if (g_ok) { ++g_pass; std::cout << "[PASS] " << name << "\n"; }
    else      { ++g_fail; std::cout << "[FAIL] " << name << "\n"; }
}
#define RUN(fn) runTest(#fn, fn)

inline int testSummary() {
    std::cout << "\n" << g_pass << " passed, " << g_fail << " failed\n";
    return g_fail == 0 ? 0 : 1;
}

inline Student mk(int id, const char* name = "Name", int batch = 2025, const char* club = "Club", int degree = 0) {
    Student s;
    s.id = id; s.name = name; s.batch = batch; s.club = club; s.degree = degree;
    return s;
}

// Insertion sort for small int arrays (tests avoid std::sort / containers on purpose).
inline void sortInts(int* a, int n) {
    for (int i = 1; i < n; ++i) {
        int v = a[i], j = i - 1;
        while (j >= 0 && a[j] > v) { a[j + 1] = a[j]; --j; }
        a[j + 1] = v;
    }
}

inline bool containsId(const int* a, int n, int id) {
    for (int i = 0; i < n; ++i) if (a[i] == id) return true;
    return false;
}

inline bool allDistinct(const int* a, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i] == a[j]) return false;
    return true;
}
