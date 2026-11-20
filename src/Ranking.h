#pragma once
#include "Record.h"
#include "LinkedList.h"

// COMPONENT 4 - Smart feature, track B: sorting-based ranking ("most connected students").   OWNER: Member 3
//
// Order = degree DESCENDING; students with equal degree are ordered by id ASCENDING,
// so the output is fully deterministic.

// Sorts items[0..n-1] in place using MERGE SORT (write it yourself; no library sort).
// n <= 1 must work (including n == 0 with items == nullptr).
void mergeSortByDegree(Student** items, int n);

// Builds a NEW array of Student* pointing at the list's students (not copies), sorted with
// mergeSortByDegree. Caller does delete[] on the array (NOT on the students).
// count = number of entries. Empty list: returns nullptr, count = 0.
// Must NOT reorder or modify the list itself.
Student** rankByDegree(const LinkedList& list, int& count);
