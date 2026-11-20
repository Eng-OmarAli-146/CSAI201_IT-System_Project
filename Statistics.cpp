#include "Statistics.h"
#include <iomanip>
#include <iostream>
#include <sstream>

// averages and percentages are always printed to two decimal places
static std::string ToTwoDecimals(double value)
{
    std::ostringstream text;
    text << std::fixed << std::setprecision(2) << value;
    return text.str();
}

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

double Statistics::CalculateAverageBusyTime()
{
    if (technicians->empty()) return 0;
    return CalculateBusyTime() / technicians->size();
}

double Statistics::CalculateUtilization()
{
    if (technicians->empty() || totalTime <= 0) return 0;
    return CalculateBusyTime() * 100.0 / (technicians->size() * totalTime);
}

int Statistics::CountRequests(RequestType type)
{
    int count = 0;
    for (size_t i = 0; i < allRequests->size(); i++)
        if ((*allRequests)[i]->getType() == type) count++;
    return count;
}

int Statistics::CountCompleted(RequestType type)
{
    int count = 0;
    for (size_t i = 0; i < completed->size(); i++)
        if ((*completed)[i]->getType() == type) count++;
    return count;
}

int Statistics::CountTechnicians(TechnicianType type)
{
    int count = 0;
    for (size_t i = 0; i < technicians->size(); i++)
        if ((*technicians)[i]->getType() == type) count++;
    return count;
}

int Statistics::CountByLocation(int lid)
{
    int count = 0;
    for (size_t i = 0; i < allRequests->size(); i++)
        if ((*allRequests)[i]->getLID() == lid) count++;
    return count;
}

std::string Statistics::IndividualBusyTimes()
{
    if (technicians->empty())
        return "none. Total = 0 minutes.";

    std::ostringstream text;
    for (size_t i = 0; i < technicians->size(); i++)
    {
        if (i > 0) text << "; ";
        text << "technician " << (*technicians)[i]->getID()
             << " = " << (*technicians)[i]->getBusyTime();
    }
    text << ". Total = " << static_cast<int>(CalculateBusyTime()) << " minutes.";
    return text.str();
}

void Statistics::GenerateReport(std::ostream& out)
{
    out << "Requests: " << static_cast<int>(allRequests->size())
        << " [NR: " << CountRequests(RequestType::NR)
        << ", SR: " << CountRequests(RequestType::SR)
        << ", UR: " << CountRequests(RequestType::UR) << "]\n";

    out << "Completed: " << getCompletedCount()
        << " [NR: " << CountCompleted(RequestType::NR)
        << ", SR: " << CountCompleted(RequestType::SR)
        << ", UR: " << CountCompleted(RequestType::UR) << "]\n";

    out << "Cancelled: " << getCancelledCount() << "\n";
    out << "Locations: " << locationCount << "\n";
    out << "Technicians: " << static_cast<int>(technicians->size())
        << " [Specialist: " << CountTechnicians(TechnicianType::ST)
        << ", General: " << CountTechnicians(TechnicianType::GT) << "]\n";

    out << "Average waiting time: "    << ToTwoDecimals(CalculateAverageWT()) << "\n";
    out << "Average resolution time: " << ToTwoDecimals(CalculateAverageRT()) << "\n";
    out << "Average busy time: "       << ToTwoDecimals(CalculateAverageBusyTime()) << "\n";
    out << "Simulation time: "         << totalTime << "\n";
    out << "Average utilisation: "     << ToTwoDecimals(CalculateUtilization()) << "%\n";

    out << "\nIndividual busy times: " << IndividualBusyTimes() << "\n";
}

// extra detail shown in interactive mode: how many tickets each location reported
void Statistics::WriteLocationCounts(std::ostream& out)
{
    if (locationCount <= 0) return;

    out << "\nTickets by location:\n";
    for (int lid = 1; lid <= locationCount; lid++)
        out << "Location " << lid << ": " << CountByLocation(lid) << "\n";
}

void Statistics::GenerateReport()
{
    GenerateReport(std::cout);
}
