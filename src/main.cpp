// Social network demo: load -> store -> index -> reachability -> ranking -> print.
// Usage: social_app [records.csv edges.csv [startId]]   (defaults: data/records.csv, data/edges.csv)
#include <iostream>
#include <string>
#include <cstdlib>
#include "LinkedList.h"
#include "HashTable.h"
#include "Graph.h"
#include "Ranking.h"
#include "Loader.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

static void printReach(const char* label, const int* ids, int n) {
    std::cout << label << " (" << n << " students): ";
    for (int i = 0; i < n; ++i) std::cout << ids[i] << (i + 1 < n ? " " : "");
    std::cout << "\n";
}

static int run(int argc, char** argv) {
    std::string recPath  = argc > 1 ? argv[1] : std::string(DATA_DIR) + "/records.csv";
    std::string edgePath = argc > 2 ? argv[2] : std::string(DATA_DIR) + "/edges.csv";

    LinkedList list;
    LoadReport recReport, edgeReport;
    if (!loadStudents(recPath.c_str(), list, recReport)) return 1;
    std::cout << "Students: " << recReport.accepted << " loaded, " << recReport.rejected << " rejected\n";
    if (list.size() == 0) { std::cout << "No students - nothing to do.\n"; return 0; }

    HashTable index(list.size() * 2 + 1);
    if (!buildIndex(list, index)) { std::cout << "[ERROR] could not build hash index\n"; return 1; }

    Graph graph(list.size());
    if (!addAllNodes(list, graph)) { std::cout << "[ERROR] could not register graph nodes\n"; return 1; }
    if (!loadEdges(edgePath.c_str(), list, graph, edgeReport, &index)) return 1;
    std::cout << "Friendships: " << edgeReport.accepted << " loaded, " << edgeReport.rejected << " rejected\n\n";

    int startId = argc > 3 ? std::atoi(argv[3]) : list.head()->data.id;
    Student* start = index.find(startId);
    if (!start) { std::cout << "Student " << startId << " not found.\n"; return 1; }
    std::cout << "Lookup " << startId << ": " << start->name << ", batch " << start->batch
              << ", club " << start->club << ", " << start->degree << " friends\n\n";

    int n = 0;
    int* order = graph.bfs(startId, n);
    printReach("BFS from start", order, n);
    delete[] order;
    order = graph.dfs(startId, n);
    printReach("DFS from start", order, n);
    delete[] order;

    int rankCount = 0;
    Student** ranked = rankByDegree(list, rankCount);
    std::cout << "\nMost connected students:\n";
    for (int i = 0; i < rankCount && i < 10; ++i)
        std::cout << "  " << (i + 1) << ". " << ranked[i]->name << " (id " << ranked[i]->id
                  << ", " << ranked[i]->degree << " friends)\n";
    delete[] ranked;
    return 0;
}

int main(int argc, char** argv) {
    int rc = run(argc, argv);  // all containers are destroyed when run() returns
#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();     // Visual Studio's leak report (shows in the Output window)
#endif
    return rc;
}
