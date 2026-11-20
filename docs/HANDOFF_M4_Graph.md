# Hand-off - Member 4: Graph (BFS / DFS)

**You own:** `src/Graph.cpp` (only this file). `Queue.h` and `Stack.h` are ready for you to use.
**Read first:** `src/Graph.h` (all contracts), `src/Queue.h`, `src/Stack.h`, `tests/test_graph.cpp`.
**Started from:** your Lab 14 graph (note what changed). You also own checking the **dataset and the expected answers** in `data/` - see below.

## Your job
- Constructor allocates `nodes_` and `adj_` for `maxNodes` entries; destructor deletes every `AdjNode` and both arrays - **never the Students**.
- `addNode`: rejects `nullptr`, a full graph, and a duplicate id. Node index = order of `addNode`.
- `addEdge(a, b)`: undirected, so add `b` to `a`'s list **and** `a` to `b`'s. Reject unknown ids, self-loops and duplicates (either direction). `edgeCount` counts each friendship once.
- `bfs` / `dfs`: return a `new int[]` of reachable IDs in visit order, start first, no repeats; unknown start returns `nullptr` with `count = 0`. Use a `bool` visited array so cycles can never hang the search.
- `test_graph` needs only plain `Student` objects, not the LinkedList, so you can finish it alone.

## Rules
No STL containers. No header edits (ask the team lead). Zero `/W4` warnings. Commit under your own name.

## Deadlines
Graphs/BFS are taught Wk 15 (Lab 14) and the final is Wk 16, so this is the tightest slot. **Read ahead now**, and have `test_graph` green by the **end of Wk 15**. Final submission: Wk 16.

## Also yours: verify the data (before Checkpoint 1)
`data/records.csv` (40 students) and `data/edges.csv` (47 friendships) are ready: groups of 17, 20 and 2 students, plus one student with no friends (id 140). Expected answers in `data/expected_bfs.txt` and `data/expected_ranking.txt` were produced by `tools/gen_expected.py`. The handout wants them **hand-computed**, so:
1. Pick 3 students, count their friends on paper, and compare with `expected_ranking.txt`.
2. Trace a BFS from 101 on paper (draw the groups) and confirm the 17-student set.
3. Say in the report that you verified them by hand and how.

## Report
Complexity of addNode/addEdge/BFS/DFS (V+E) with justification; trade-offs vs adjacency matrix and edge list; your "what I built" paragraph.

## Viva - be ready to explain
Why a visited array? Why store indices and not pointers in the adjacency lists? What does `indexOf` cost, and what would you change to fix it? Live-modify: add a `shortestDistance(a, b)` using BFS levels.
