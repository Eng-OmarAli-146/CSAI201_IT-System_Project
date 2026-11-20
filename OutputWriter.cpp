#include "OutputWriter.h"
#include <algorithm>

// completed rows are sorted by ascending FT, then ascending RID
static bool ComesFirst(Ticket* a, Ticket* b)
{
    if (a->getFT() != b->getFT()) return a->getFT() < b->getFT();
    return a->getRID() < b->getRID();
}

void OutputWriter::WriteCompletedTickets()
{
    out << "FT RID QT WT ST AT TID LID\n";

    std::vector<Ticket*> rows = *completed;
    std::sort(rows.begin(), rows.end(), ComesFirst);

    for (size_t i = 0; i < rows.size(); i++)
    {
        Ticket* t = rows[i];
        out << t->getFT() << " " << t->getRID() << " " << t->getQT() << " "
            << t->getST() - t->getQT() << " "
            << t->getST() << " " << t->getAT() << " "
            << t->getTID() << " " << t->getLID() << "\n";
    }
}

void OutputWriter::WriteStatistics()
{
    out << "\n";
    stats->GenerateReport(out);
}

void OutputWriter::WriteOutputFile()
{
    out.open("output.txt");
    WriteCompletedTickets();
    WriteStatistics();
    out.close();
}
