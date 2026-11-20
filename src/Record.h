#pragma once
#include <string>

// Shared record type. AGREED AT KICKOFF - do not change without telling the team lead.
// Only LinkedList owns Student objects. Everyone else stores Student* (never delete them).
struct Student {
    int         id;      // unique, positive
    std::string name;
    int         batch;   // e.g. 2025
    std::string club;
    int         degree;  // number of friends; filled in by the Loader (starts at 0)
};
