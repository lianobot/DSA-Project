#pragma once
#include "LinkedList.h"
#include "HashTable.h"
#include "Graph.h"

// File loading + validation.   OWNER: Member 1 (team lead).
// Rejected rows are reported on std::cout ("[REJECTED] <file> line N: reason") and counted.

struct LoadReport {
    int accepted = 0;
    int rejected = 0;
};

// records.csv:  id,name,batch,club   (a header line starting with "id" is skipped)
// Rejects: duplicate id, wrong number of fields, non-numeric / non-positive id or batch, empty name.
// Returns false only if the file cannot be opened.
bool loadStudents(const char* path, LinkedList& list, LoadReport& report);

// edges.csv:  source_id,target_id   (a header line starting with "source_id" is skipped)
// Rejects: unknown id, self-loop, duplicate friendship, malformed row.
// For every accepted edge: graph.addEdge(...) and degree++ on BOTH students.
// Students are looked up with index->find(id) if index != nullptr, else list.findById(id).
// Precondition: all students are already registered in the graph (see addAllNodes).
// Returns false only if the file cannot be opened.
bool loadEdges(const char* path, LinkedList& list, Graph& graph, LoadReport& report,
               const HashTable* index = nullptr);

// Registers every student in the list with the graph. Returns false if any addNode fails.
bool addAllNodes(const LinkedList& list, Graph& graph);

// Inserts every student in the list into the hash table. Returns false if any insert fails.
bool buildIndex(const LinkedList& list, HashTable& index);
