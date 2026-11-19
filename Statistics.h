#pragma once
#include <vector>
#include "Ticket.h"
#include "Technician.h"

class Statistics
{
    std::vector<Ticket*>*     completed;
    std::vector<Ticket*>*     cancelled;
    std::vector<Technician*>* technicians;
    int totalTime;

public:
    Statistics(std::vector<Ticket*>* c, std::vector<Ticket*>* x,
               std::vector<Technician*>* t, int time)
        : completed(c), cancelled(x), technicians(t), totalTime(time) {}

    double CalculateAverageWT();
    double CalculateAverageRT();
    double CalculateBusyTime();
    double CalculateUtilization();
    void   GenerateReport();

    int getCompletedCount() { return completed->size(); }
    int getCancelledCount() { return cancelled->size(); }
};
