#pragma once
#include <vector>
#include "Ticket.h"
#include "Technician.h"
#include "WaitingNRQueue.h"
#include "InServiceList.h"
#include "AvailableGTQueue.h"

struct CancellationRequest
{
    int CT;
    int RID;
};

class CancellationManager
{
    WaitingNRQueue*           waitingNR;
    InServiceList*            inService;
    AvailableGTQueue*         availableGT;
    std::vector<Technician*>* technicians;
    std::vector<Ticket*>*     cancelled;

public:
    CancellationManager(WaitingNRQueue* w, InServiceList* s, AvailableGTQueue* g,
                        std::vector<Technician*>* t, std::vector<Ticket*>* c)
        : waitingNR(w), inService(s), availableGT(g), technicians(t), cancelled(c) {}

    bool CancelTicket(int RID);
    bool CancelWaitingNR(int RID);
    bool CancelAssignedNR(int RID);
};
