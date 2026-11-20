# CS-250 Semester Project Report - Social Network (Domain A)
Team: (names + Reg. Nos)    Roles: (as recorded at kickoff)

## 1. Domain and dataset
Domain A (undirected friendships). 40 students, 47 friendships, three friend groups of 17, 20 and 2 students plus one student with no friends. Files: `data/records.csv`, `data/edges.csv`. Expected answers verified by hand: (say exactly how; who).

## 2. Components, complexity and trade-offs
| Component | Operation | Big-O | One-sentence justification |
|---|---|---|---|
| Linked list | insert (with duplicate check) | O(n) | must scan for the id first |
| | insert without check (tail pointer) | O(1) | |
| | findById / at(i) | O(n) (Omega(1) if first) | linear scan |
| Hash table (chaining) | insert / find | O(1) average, O(n) worst | worst case: every key in one bucket |
| Graph (adjacency list) | addEdge (with duplicate check) | (fill in, depends on your code) | |
| | BFS / DFS | O(V+E) | each node and edge visited once |
| Merge sort ranking | sort | Theta(n log n) | all cases; O(n) extra memory |

For **each** component write: *what we gained, what we gave up* vs at least one alternative (dynamic array; BST / sorted array; adjacency matrix; quicksort / heap). Do not just argue the choice was right.

## 3. Timing comparison (exactly one)
Paste the `bench_timing` table (5 sizes). State whether it matches the Big-O claims above and why / why not. Machine, compiler, Release/Debug.

## 4. Testing summary
Unit tests per component (counts), the 5 edge cases, the integration test. Results: (pass/fail honestly).

## 5. What does not work / known limitations
(Be specific. Anything not tested must be listed here. Do not claim untested features.)

## 6. Attribution
- Lab code reused: per component, which lab, what changed.
- Teammate code: (none, or name + what).
- AI tools: headers, test files, Loader, main, CMake, Queue/Stack, dataset and tools were scaffolded with Claude and reviewed by the team lead; the core logic of each .cpp (LinkedList, HashTable, Graph, Ranking) was written by its owner.
- Bonus work (if any): clearly marked, max +5 on the 50-point scale.

## 7. Individual contributions (one paragraph each)
Member 1 / 2 / 3 / 4: what you built, which files, which tests you added, how it connects to the others.
