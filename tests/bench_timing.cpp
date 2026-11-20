// The ONE required timing comparison (handout section 8): hash lookup vs linear scan of the linked list.
// Run it, paste the table into the report, and say whether the numbers match your Big-O claims.
#include <chrono>
#include <iomanip>
#include <iostream>
#include "LinkedList.h"
#include "HashTable.h"

int main() {
    const int sizes[5]   = { 1000, 5000, 10000, 50000, 100000 };
    const int LOOKUPS    = 1000;
    volatile long sink   = 0;   // stops the compiler from deleting the lookups

    std::cout << "records   list scan (ns/lookup)   hash (ns/lookup)   ratio\n";
    for (int k = 0; k < 5; ++k) {
        int n = sizes[k];
        LinkedList list;
        HashTable hash(n);                      // load factor about 1
        for (int id = 1; id <= n; ++id) {
            Student s;
            s.id = id; s.name = "x"; s.batch = 2025; s.club = "c"; s.degree = 0;
            Student* p = list.insertUnchecked(s);   // no duplicate check: keeps setup fast
            if (!p || !hash.insert(p)) { std::cout << "LinkedList/HashTable not implemented yet.\n"; return 1; }
        }
        int target = n;                          // last inserted id = worst case for the list scan

        auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < LOOKUPS; ++i) { Student* p = list.findById(target); sink += p ? p->id : 0; }
        auto t1 = std::chrono::steady_clock::now();
        for (int i = 0; i < LOOKUPS; ++i) { Student* p = hash.find(target); sink += p ? p->id : 0; }
        auto t2 = std::chrono::steady_clock::now();

        double listNs = std::chrono::duration<double, std::nano>(t1 - t0).count() / LOOKUPS;
        double hashNs = std::chrono::duration<double, std::nano>(t2 - t1).count() / LOOKUPS;
        std::cout << std::setw(7) << n << std::setw(22) << std::fixed << std::setprecision(1) << listNs
                  << std::setw(19) << hashNs << std::setw(10) << std::setprecision(0) << (hashNs > 0 ? listNs / hashNs : 0) << "x\n";
    }
    std::cout << "\nExpected: list time grows about linearly with n; hash time stays roughly flat.\n"
                 "If your numbers disagree, report that honestly and explain why.\n";
    return 0;
}
