#include "OutputWriter.h"

// completed rows are sorted by ascending FT, then ascending RID
static bool ComesFirst(Ticket* a, Ticket* b)
{
    if (a->getFT() != b->getFT()) return a->getFT() < b->getFT();
    return a->getRID() < b->getRID();
}

void OutputWriter::WriteCompletedTickets()
{
    out << "FT RID QT WT ST AT TID LID\n";

    // small hand-written selection sort on a copy of the completed array
    Ticket** rows = new Ticket*[completedCount > 0 ? completedCount : 1];
    for (int i = 0; i < completedCount; i++)
        rows[i] = completed[i];

    for (int i = 0; i < completedCount - 1; i++)
    {
        int best = i;
        for (int j = i + 1; j < completedCount; j++)
            if (ComesFirst(rows[j], rows[best])) best = j;

        Ticket* temp = rows[i];
        rows[i] = rows[best];
        rows[best] = temp;
    }

    for (int i = 0; i < completedCount; i++)
    {
        Ticket* t = rows[i];
        out << t->getFT() << " " << t->getRID() << " " << t->getQT() << " "
            << t->getST() - t->getQT() << " "
            << t->getST() << " " << t->getAT() << " "
            << t->getTID() << " " << t->getLID() << "\n";
    }

    delete[] rows;
}

void OutputWriter::WriteStatistics()
{
    stats->GenerateReport(out);
}

bool OutputWriter::WriteOutputFile()
{
    out.open(fileName.c_str());
    if (!out.is_open()) return false;

    WriteCompletedTickets();
    WriteStatistics();
    out.close();
    return true;
}
