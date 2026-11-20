#pragma once
#include "Definitions.h"
#include "Ticket.h"
#include "Technician.h"
#include "WaitingNRQueue.h"
#include "InServiceList.h"
#include "AvailableGTQueue.h"
#include "AvailableSTQueue.h"
#include "TicketQueue.h"

class CancellationManager
{
    WaitingNRQueue*   waitingNR;
    InServiceList*    inService;
    AvailableGTQueue* availableGT;
    AvailableSTQueue* availableST;
    Technician**      technicians;
    int               technicianCount;
    TicketQueue*      cancelled;

public:
    CancellationManager(WaitingNRQueue* w, InServiceList* s, AvailableGTQueue* g,
                        AvailableSTQueue* st, Technician** t, int count,
                        TicketQueue* c)
        : waitingNR(w), inService(s), availableGT(g), availableST(st),
          technicians(t), technicianCount(count), cancelled(c) {}

    bool CancelTicket(int RID, int currentTime);
    bool CancelWaitingNR(int RID);
    bool CancelAssignedNR(int RID, int currentTime);
};
