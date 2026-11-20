# CS-250 Semester Project - Social Network (Domain A), Fall 2026

Console program: load students + friendships -> store (linked list) -> index (hash table) -> reachability (graph, BFS/DFS) -> ranking (merge sort) -> print.

## Opening and running it (Visual Studio 2019/2022)

1. Install the **"Desktop development with C++"** workload (it includes CMake support).
2. **File > Open > Folder...** and pick this folder (the one with `CMakeLists.txt`). Wait for "CMake generation finished".
3. Top toolbar: choose a startup item (`social\_app`, or any `test\_\*`) and press **Run** (Ctrl+F5).
4. **Test > Test Explorer** (or Test > Run CTests) runs every test executable at once.
5. Warnings show in the Error List. We build at `/W4`: **fix every warning in your own file.**

Without VS: `cmake -S . -B build \&\& cmake --build build \&\& ctest --test-dir build --output-on-failure`.

## Layout

```
src/    Record.h  LinkedList  HashTable  Graph  Ranking  Loader  Queue.h  Stack.h  main.cpp
tests/  one test file per component, test\_integration.cpp, bench\_timing.cpp (the ONE timing comparison)
data/   records.csv, edges.csv (real data) + bad\_\*.csv, empty\_records.csv, fake\_small\_\*.csv (test data)
        expected\_bfs.txt, expected\_ranking.txt (the answers the integration test checks against)
docs/   HANDOFF\_\*.md (one per teammate), REPORT\_TEMPLATE.md, LEAD\_CHECKLIST.md
tools/  check\_rules.sh (strict g++ build + banned-STL scan), gen\_expected.py
```

## Who writes what

|File(s)|Owner|Test file that must go green|
|-|-|-|
|`src/LinkedList.cpp`|Member 1|`test\_linkedlist`|
|`src/HashTable.cpp`|Member 2|`test\_hashtable` (+ run `bench\_timing`)|
|`src/Ranking.cpp`|Member 3|`test\_ranking`|
|`src/Graph.cpp`|Member 4|`test\_graph`|
|headers, `Loader.cpp`, `main.cpp`, dataset, shared tests, CMake|team lead (Member 1)|`test\_loader`, `test\_integration`|

**Headers are the contract.** Do not edit a `.h` file. If you need another private member or helper, message the team lead, who edits the header and tells everyone.

## Coding conventions (agreed at kickoff)

* Classes `PascalCase`; functions and variables `camelCase`; private data members end with `\_`; constants `UPPER\_CASE`.
* 4 spaces, no tabs; opening brace on the same line; one class per `.h/.cpp` pair; `#pragma once`.
* No `using namespace std;`. Standard C++17 only (no `scanf\_s`, no `pch.h`, no `<windows.h>`): the graders build with g++.
* Raw pointers + manual memory. **Every `new` has a matching `delete` in a destructor.** Only `LinkedList` owns `Student` objects.
* **No STL containers in Components 1-4** (`vector list deque stack queue map unordered\_map set priority\_queue`, also no `std::sort`). `std::string`, `iostream`, `fstream`, `chrono` are fine.
* Commit under your **own** name, small and often, with messages like `HashTable: implement find()`.

## Attribution (copy into the report)

* Each member records which lab each of their `.cpp` files started from and what changed.

