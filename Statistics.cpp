#include "Statistics.h"
#include <iomanip>

Statistics::Statistics(Ticket** completed, int completedCount,
                       Ticket** cancelled, int cancelledCount,
                       Ticket** allRequests, int requestCount,
                       Technician** technicians, int technicianCount,
                       int locationCount, int totalTime)
{
    this->completed = completed;
    this->completedCount = completedCount;
    this->cancelled = cancelled;
    this->cancelledCount = cancelledCount;
    this->allRequests = allRequests;
    this->requestCount = requestCount;
    this->technicians = technicians;
    this->technicianCount = technicianCount;
    this->locationCount = locationCount;
    this->totalTime = totalTime;
}

// WT = ST - QT  (cancelled tickets are never counted here)
double Statistics::CalculateAverageWT()
{
    if (completedCount == 0) return 0;

    double sum = 0;
    for (int i = 0; i < completedCount; i++)
        sum += completed[i]->getST() - completed[i]->getQT();

    return sum / completedCount;
}

// resolution time = FT - QT
double Statistics::CalculateAverageRT()
{
    if (completedCount == 0) return 0;

    double sum = 0;
    for (int i = 0; i < completedCount; i++)
        sum += completed[i]->getFT() - completed[i]->getQT();

    return sum / completedCount;
}

double Statistics::CalculateBusyTime()
{
    double sum = 0;
    for (int i = 0; i < technicianCount; i++)
        sum += technicians[i]->getBusyTime();

    return sum;
}

double Statistics::CalculateAverageBusyTime()
{
    if (technicianCount == 0) return 0;
    return CalculateBusyTime() / technicianCount;
}

double Statistics::CalculateUtilization()
{
    if (technicianCount == 0 || totalTime <= 0) return 0;
    return CalculateBusyTime() * 100.0 / (technicianCount * totalTime);
}

int Statistics::CountRequests(RequestType type)
{
    int count = 0;
    for (int i = 0; i < requestCount; i++)
        if (allRequests[i]->getType() == type) count++;

    return count;
}

int Statistics::CountCompleted(RequestType type)
{
    int count = 0;
    for (int i = 0; i < completedCount; i++)
        if (completed[i]->getType() == type) count++;

    return count;
}

int Statistics::CountTechnicians(TechnicianType type)
{
    int count = 0;
    for (int i = 0; i < technicianCount; i++)
        if (technicians[i]->getType() == type) count++;

    return count;
}

int Statistics::CountByLocation(int lid)
{
    int count = 0;
    for (int i = 0; i < requestCount; i++)
        if (allRequests[i]->getLID() == lid) count++;

    return count;
}

void Statistics::GenerateReport(std::ostream& out)
{
    out << "Requests: " << requestCount
        << " [NR: " << CountRequests(RequestType::NR)
        << ", SR: " << CountRequests(RequestType::SR)
        << ", UR: " << CountRequests(RequestType::UR) << "]\n";

    out << "Completed: " << completedCount
        << " [NR: " << CountCompleted(RequestType::NR)
        << ", SR: " << CountCompleted(RequestType::SR)
        << ", UR: " << CountCompleted(RequestType::UR) << "]\n";

    out << "Cancelled: " << cancelledCount << "\n";
    out << "Locations: " << locationCount << "\n";
    out << "Technicians: " << technicianCount
        << " [Specialist: " << CountTechnicians(TechnicianType::ST)
        << ", General: " << CountTechnicians(TechnicianType::GT) << "]\n";

    // every average and percentage is printed with two decimals
    out << std::fixed << std::setprecision(2);
    out << "Average waiting time: "    << CalculateAverageWT() << "\n";
    out << "Average resolution time: " << CalculateAverageRT() << "\n";
    out << "Average busy time: "       << CalculateAverageBusyTime() << "\n";
    out << "Simulation time: "         << totalTime << "\n";
    out << "Average utilisation: "     << CalculateUtilization() << "%\n";

    out << "Individual busy times: ";
    if (technicianCount == 0) out << "none";
    for (int i = 0; i < technicianCount; i++)
    {
        if (i > 0) out << "; ";
        out << "technician " << technicians[i]->getID() << " = " << technicians[i]->getBusyTime();
    }
    out << ". Total = " << static_cast<int>(CalculateBusyTime()) << " minutes.\n";

    // extra detail: how many tickets each location reported
    if (locationCount > 0)
    {
        out << "\nTickets by location:\n";
        for (int lid = 1; lid <= locationCount; lid++)
            out << "Location " << lid << ": " << CountByLocation(lid) << "\n";
    }
}

void Statistics::GenerateReport()
{
    GenerateReport(std::cout);
}
