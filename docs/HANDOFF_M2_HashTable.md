# Hand-off - Member 2: HashTable

**You own:** `src/HashTable.cpp` (only this file; also run `tests/bench_timing.cpp`).
**Read first:** `src/HashTable.h` - every function has its contract written above it. Also read `tests/test_hashtable.cpp`.
**Started from:** your Lab 13 hash table (note in the report what you changed).

## Your job
Replace every stub body in `HashTable.cpp` so that `test_hashtable` is all green:
- `HashTable(n)` allocates `n` bucket heads (all `nullptr`); `n < 1` becomes 1.
- Separate chaining. `insert` rejects `nullptr` and duplicate IDs. `find` returns the **same pointer** that was inserted.
- `bucketOf(id)` = id mod bucketCount (never negative). `bucketLength(b)` counts the chain.
- Destructor deletes every chain node and the bucket array - **never the Students** (the LinkedList owns them).

## Rules
No STL containers. No header edits (ask the team lead). Zero `/W4` warnings in your file. Commit under your own name.

## Deadlines
Standalone on fake data: **before Wk 14** (hashing is taught Wk 14 / Lab 13; start reading early). Hash index working over the real store and the forced-collision demo: **Checkpoint 3, Wk 15 lab**.

## Also yours
1. Run `bench_timing` (Release build) and paste the 5-row table into the report with 3-4 sentences: do the timings match your Big-O claims?
2. Write your part of the report: complexity of insert/find/worst case, trade-offs vs a sorted array, a binary search tree and an open-addressing table (what you gain *and* give up), and your "what I built" paragraph.
3. Add 2+ tests of your own at the marked spot in `test_hashtable.cpp` (e.g. a larger table, insert-order independence) - you must be able to explain them in the viva.

## Viva - be ready to explain
Why chaining? What is the load factor in `bench_timing`? Why does `find` return the stored pointer instead of a copy? What happens in your table when everything collides? Live-modify: change the hash function, or make the table report its longest chain.
