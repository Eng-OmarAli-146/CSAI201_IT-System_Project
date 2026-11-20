#pragma once
#include <iostream>
#include "Ticket.h"
#include "Technician.h"

// Computes and prints everything the project asks for at the end of a run.
class Statistics
{
    Ticket**     completed;      // completed tickets, in FT then RID order
    int          completedCount;
    Ticket**     cancelled;      // accepted cancellations
    int          cancelledCount;
    Ticket**     allRequests;    // every request of the input file
    int          requestCount;
    Technician** technicians;
    int          technicianCount;
    int          locationCount;
    int          totalTime;      // final simulation minute

public:
    Statistics(Ticket** completed, int completedCount,
               Ticket** cancelled, int cancelledCount,
               Ticket** allRequests, int requestCount,
               Technician** technicians, int technicianCount,
               int locationCount, int totalTime);

    double CalculateAverageWT();
    double CalculateAverageRT();
    double CalculateBusyTime();
    double CalculateAverageBusyTime();
    double CalculateUtilization();

    int CountRequests(RequestType type);
    int CountCompleted(RequestType type);
    int CountTechnicians(TechnicianType type);
    int CountByLocation(int lid);

    int getCompletedCount() { return completedCount; }
    int getCancelledCount() { return cancelledCount; }

    void GenerateReport(std::ostream& out);
    void GenerateReport();
};
