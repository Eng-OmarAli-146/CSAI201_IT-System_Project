#pragma once
#include <fstream>
#include <string>
#include "Ticket.h"
#include "Statistics.h"

class OutputWriter
{
    std::ofstream out;
    Ticket**      completed;
    int           completedCount;
    Statistics*   stats;
    std::string   fileName;

public:
    OutputWriter(Ticket** completed, int completedCount,
                 Statistics* stats, const std::string& fileName)
        : completed(completed), completedCount(completedCount),
          stats(stats), fileName(fileName) {}

    void WriteCompletedTickets();
    void WriteStatistics();
    bool WriteOutputFile();     // false if the file could not be created
};
