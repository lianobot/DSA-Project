#include "Loader.h"
#include <fstream>
#include <iostream>
#include <string>

namespace {

std::string trim(const std::string& s) {
    size_t b = 0, e = s.size();
    while (b < e && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r' || s[b] == '\n')) ++b;
    while (e > b && (s[e - 1] == ' ' || s[e - 1] == '\t' || s[e - 1] == '\r' || s[e - 1] == '\n')) --e;
    return s.substr(b, e - b);
}

// Splits line on commas into fields[0..expected-1]. Returns false unless there are exactly `expected` fields.
bool splitFields(const std::string& line, std::string* fields, int expected) {
    int n = 0;
    size_t start = 0;
    while (true) {
        size_t comma = line.find(',', start);
        std::string piece = (comma == std::string::npos) ? line.substr(start) : line.substr(start, comma - start);
        if (n >= expected) return false;
        fields[n++] = trim(piece);
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    return n == expected;
}

// Accepts only a positive integer written with digits (max 9 digits).
bool parsePositiveInt(const std::string& s, int& out) {
    if (s.empty() || s.size() > 9) return false;
    int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
        v = v * 10 + (s[i] - '0');
    }
    if (v <= 0) return false;
    out = v;
    return true;
}

void reject(LoadReport& report, const char* path, int lineNo, const std::string& reason) {
    ++report.rejected;
    std::cout << "[REJECTED] " << path << " line " << lineNo << ": " << reason << "\n";
}

}  // namespace

bool loadStudents(const char* path, LinkedList& list, LoadReport& report) {
    std::ifstream in(path);
    if (!in) {
        std::cout << "[ERROR] cannot open " << path << "\n";
        return false;
    }
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        if (trim(line).empty()) continue;
        std::string f[4];
        if (!splitFields(line, f, 4)) {
            if (lineNo == 1 && trim(line).compare(0, 2, "id") == 0) continue;  // header with odd shape
            reject(report, path, lineNo, "expected 4 fields (id,name,batch,club)");
            continue;
        }
        if (lineNo == 1 && f[0] == "id") continue;  // header
        Student s;
        if (!parsePositiveInt(f[0], s.id)) { reject(report, path, lineNo, "invalid id '" + f[0] + "'"); continue; }
        if (f[1].empty()) { reject(report, path, lineNo, "empty name"); continue; }
        if (!parsePositiveInt(f[2], s.batch)) { reject(report, path, lineNo, "invalid batch '" + f[2] + "'"); continue; }
        s.name = f[1];
        s.club = f[3];
        s.degree = 0;
        if (!list.insert(s)) { reject(report, path, lineNo, "duplicate ID " + f[0]); continue; }
        ++report.accepted;
    }
    return true;
}

bool loadEdges(const char* path, LinkedList& list, Graph& graph, LoadReport& report, const HashTable* index) {
    std::ifstream in(path);
    if (!in) {
        std::cout << "[ERROR] cannot open " << path << "\n";
        return false;
    }
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        if (trim(line).empty()) continue;
        std::string f[2];
        if (!splitFields(line, f, 2)) {
            reject(report, path, lineNo, "expected 2 fields (source_id,target_id)");
            continue;
        }
        if (lineNo == 1 && f[0] == "source_id") continue;  // header
        int a = 0, b = 0;
        if (!parsePositiveInt(f[0], a) || !parsePositiveInt(f[1], b)) {
            reject(report, path, lineNo, "non-numeric or non-positive id");
            continue;
        }
        Student* sa = index ? index->find(a) : list.findById(a);
        Student* sb = index ? index->find(b) : list.findById(b);
        if (!sa || !sb) {
            reject(report, path, lineNo, "edge references unknown ID (" + f[0] + "," + f[1] + ")");
            continue;
        }
        if (a == b) { reject(report, path, lineNo, "self-loop on ID " + f[0]); continue; }
        if (graph.hasEdge(a, b)) { reject(report, path, lineNo, "duplicate friendship (" + f[0] + "," + f[1] + ")"); continue; }
        if (!graph.addEdge(a, b)) { reject(report, path, lineNo, "graph refused edge (" + f[0] + "," + f[1] + ")"); continue; }
        ++sa->degree;
        ++sb->degree;
        ++report.accepted;
    }
    return true;
}

bool addAllNodes(const LinkedList& list, Graph& graph) {
    for (LinkedList::Node* n = list.head(); n; n = n->next) {
        if (!graph.addNode(&n->data)) return false;
    }
    return true;
}

bool buildIndex(const LinkedList& list, HashTable& index) {
    for (LinkedList::Node* n = list.head(); n; n = n->next) {
        if (!index.insert(&n->data)) return false;
    }
    return true;
}
