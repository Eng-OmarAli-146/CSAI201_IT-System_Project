#pragma once
#include <ostream>
#include <string>
#include <vector>
#include "Ticket.h"
#include "Technician.h"

class Statistics
{
    std::vector<Ticket*>*     completed;
    std::vector<Ticket*>*     cancelled;
    std::vector<Technician*>* technicians;
    std::vector<Ticket*>*     allRequests;
    int locationCount;
    int totalTime;

public:
    Statistics(std::vector<Ticket*>* c, std::vector<Ticket*>* x,
               std::vector<Technician*>* t, std::vector<Ticket*>* r,
               int locations, int time)
        : completed(c), cancelled(x), technicians(t), allRequests(r),
          locationCount(locations), totalTime(time) {}

    double CalculateAverageWT();
    double CalculateAverageRT();
    double CalculateBusyTime();
    double CalculateAverageBusyTime();
    double CalculateUtilization();

    int CountRequests(RequestType type);
    int CountCompleted(RequestType type);
    int CountTechnicians(TechnicianType type);
    int CountByLocation(int lid);
    std::string IndividualBusyTimes();

    void GenerateReport(std::ostream& out);
    void GenerateReport();
    void WriteLocationCounts(std::ostream& out);

    int getCompletedCount() { return static_cast<int>(completed->size()); }
    int getCancelledCount() { return static_cast<int>(cancelled->size()); }
};
