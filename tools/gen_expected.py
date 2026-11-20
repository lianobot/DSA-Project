#!/usr/bin/env python3
"""Independent cross-check for the C++ results. Reads data/records.csv + data/edges.csv and writes
data/expected_bfs.txt and data/expected_ranking.txt using plain Python (no shared code with the C++ project).
The handout asks for HAND-computed answers: use this to confirm, but ALSO verify a few by hand
(count the friends of a student on paper; trace one component) and sign off in the report.
Run from the project root:  python3 tools/gen_expected.py"""
import csv
from collections import deque, defaultdict

students = [int(r["id"]) for r in csv.DictReader(open("data/records.csv"))]
adj = defaultdict(set)
for r in csv.DictReader(open("data/edges.csv")):
    a, b = int(r["source_id"]), int(r["target_id"])
    adj[a].add(b); adj[b].add(a)

def reach(s):
    seen = {s}; q = deque([s])
    while q:
        u = q.popleft()
        for v in adj[u]:
            if v not in seen: seen.add(v); q.append(v)
    return sorted(seen)

starts = [101, 118, 138, 140, 133]
with open("data/expected_bfs.txt", "w") as f:
    f.write("# start: sorted list of every ID reachable from start (including start)\n")
    for s in starts:
        f.write(f"{s}: {' '.join(map(str, reach(s)))}\n")

rank = sorted(students, key=lambda i: (-len(adj[i]), i))
with open("data/expected_ranking.txt", "w") as f:
    f.write("# position order: degree descending, ties by id ascending.  Format: id degree\n")
    for i in rank:
        f.write(f"{i} {len(adj[i])}\n")
print("wrote data/expected_bfs.txt and data/expected_ranking.txt")
