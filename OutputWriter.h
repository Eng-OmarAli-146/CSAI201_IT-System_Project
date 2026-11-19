#pragma once
#include <vector>
#include <fstream>
#include "Ticket.h"
#include "Statistics.h"

class OutputWriter
{
    std::ofstream         out;
    std::vector<Ticket*>* completed;
    Statistics*           stats;

public:
    OutputWriter(std::vector<Ticket*>* c, Statistics* s) : completed(c), stats(s) {}

    void WriteCompletedTickets();
    void WriteStatistics();
    void WriteOutputFile();
};
