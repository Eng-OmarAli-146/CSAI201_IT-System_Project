#include "OutputWriter.h"

void OutputWriter::WriteCompletedTickets()
{
    out << "FT RID QT WT ST AT TID LID\n";
    for (size_t i = 0; i < completed->size(); i++)
    {
        Ticket* t = (*completed)[i];
        out << t->getFT() << " " << t->getRID() << " " << t->getQT() << " "
            << t->getST() - t->getQT() << " "
            << t->getST() << " " << t->getAT() << " "
            << t->getTID() << " " << t->getLID() << "\n";
    }
}

void OutputWriter::WriteStatistics()
{
    out << "\nCompleted Count: " << stats->getCompletedCount()
        << "\nCancelled Count: " << stats->getCancelledCount()
        << "\nAverage WT: "      << stats->CalculateAverageWT()
        << "\nAverage RT: "      << stats->CalculateAverageRT()
        << "\nBusy Time: "       << stats->CalculateBusyTime()
        << "\nUtilization: "     << stats->CalculateUtilization() << " %\n";
}

void OutputWriter::WriteOutputFile()
{
    out.open("output.txt");
    WriteCompletedTickets();
    WriteStatistics();
    out.close();
}
