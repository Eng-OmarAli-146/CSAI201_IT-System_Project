#include "Statistics.h"
#include <iostream>

double Statistics::CalculateAverageWT()
{
    if (completed->empty()) return 0;
    double sum = 0;
    for (size_t i = 0; i < completed->size(); i++)
        sum += (*completed)[i]->getST() - (*completed)[i]->getQT();   // WT = ST - QT
    return sum / completed->size();
}

double Statistics::CalculateAverageRT()
{
    if (completed->empty()) return 0;
    double sum = 0;
    for (size_t i = 0; i < completed->size(); i++)
        sum += (*completed)[i]->getFT() - (*completed)[i]->getQT();   // RT = FT - QT
    return sum / completed->size();
}

double Statistics::CalculateBusyTime()
{
    double sum = 0;
    for (size_t i = 0; i < technicians->size(); i++)
        sum += (*technicians)[i]->getBusyTime();
    return sum;
}

double Statistics::CalculateUtilization()
{
    if (technicians->empty() || totalTime <= 0) return 0;
    return CalculateBusyTime() * 100.0 / (technicians->size() * totalTime);
}

void Statistics::GenerateReport()
{
    std::cout << "\nCompleted: "   << getCompletedCount()
              << "\nCancelled: "   << getCancelledCount()
              << "\nAverage WT: "  << CalculateAverageWT()
              << "\nAverage RT: "  << CalculateAverageRT()
              << "\nBusy Time: "   << CalculateBusyTime()
              << "\nUtilization: " << CalculateUtilization() << " %\n";
}
