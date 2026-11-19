#include "Scheduler.h"

// Order: UR first, then SR, then NR
void Scheduler::AssignTickets(int currentTime)
{
    AssignUR(currentTime);
    AssignSR(currentTime);
    AssignNR(currentTime);
}

// UR: take highest priority, try GT, else ST
void Scheduler::AssignUR(int currentTime)
{
    while (!waitingUR->isEmpty())
    {
        Technician* tech = nullptr;

        if (!availableGT->isEmpty())
            tech = availableGT->getGT();
        else if (!availableST->isEmpty())
            tech = availableST->getST();
        else
            break;                       // nobody free

        Ticket* t = waitingUR->removeHighest();
        AssignTicket(t, tech, currentTime);
    }
}

// SR: take first SR, assign ST
void Scheduler::AssignSR(int currentTime)
{
    while (!waitingSR->isEmpty() && !availableST->isEmpty())
    {
        Technician* tech = availableST->getST();
        Ticket* t = waitingSR->dequeue();
        AssignTicket(t, tech, currentTime);
    }
}

// NR: take first NR, assign GT
void Scheduler::AssignNR(int currentTime)
{
    while (!waitingNR->isEmpty() && !availableGT->isEmpty())
    {
        Technician* tech = availableGT->getGT();
        Ticket* t = waitingNR->dequeue();
        AssignTicket(t, tech, currentTime);
    }
}

void Scheduler::AssignTicket(Ticket* t, Technician* tech, int currentTime)
{
    int duration = configs->getDuration(t->getPC());

    t->setAT(currentTime);
    t->setST(currentTime);
    t->setFT(currentTime + duration);
    t->setTID(tech->getID());
    t->setStatus(IN_SERVICE);

    tech->assignTicket(t);
    inService->insert(t);
}
