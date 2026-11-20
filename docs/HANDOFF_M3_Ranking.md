# Hand-off - Member 3: Ranking (merge sort)

**You own:** `src/Ranking.cpp` (only this file).
**Read first:** `src/Ranking.h` (the order rule: degree descending, ties by id ascending) and `tests/test_ranking.cpp`.
**Started from:** your merge/quick-sort lab (Wk 12) - note what you changed.

## Your job
- `mergeSortByDegree(Student** items, int n)`: merge sort **in place on the pointer array**, written by you (no `std::sort`). `n == 0` with `nullptr` must not crash. Use a temporary array you `new[]` and `delete[]`.
- `rankByDegree(const LinkedList&, int& count)`: copy the list's student *pointers* into a new array, sort, return it. Empty list: `nullptr` and `count = 0`. **Never reorder the list.**
- The first six tests need no LinkedList at all, so you can finish them on day one. The last two need the team lead's `LinkedList` (a stub until Checkpoint 1; they will turn green once it exists).

## Rules
No STL containers. No header edits (ask the team lead). Zero `/W4` warnings. Commit under your own name.

## Deadlines
Checkpoint 2, **end of Wk 13**: ranking working over the real store (`test_ranking` green, and the "most connected" list visible in `social_app`). Merge sort is taught Wk 12, so you can start right after that lecture.

## Also yours
1. Add 2+ tests of your own at the marked spot in `test_ranking.cpp`.
2. Report section: Big-Theta of merge sort with justification (best/worst/average), why O(n) extra memory, trade-offs vs quicksort, heap/AVL leaderboard and insertion sort; your "what I built" paragraph.

## Viva - be ready to explain
Why is merge sort Theta(n log n) in *all* cases? Why a temp array? Why does the tie-break on id matter for testing? Live-modify: sort ascending, or rank by batch then degree.
