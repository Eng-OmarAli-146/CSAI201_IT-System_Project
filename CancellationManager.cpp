#include "CancellationManager.h"

// Only NR tickets may be cancelled. SR, UR, unknown ids, completed and
// already cancelled tickets are ignored by the two steps below.
bool CancellationManager::CancelTicket(int RID, int currentTime)
{
    if (CancelWaitingNR(RID))
        return true;
    return CancelAssignedNR(RID, currentTime);   // else: ignore
}

// NR that is still waiting: remove it without changing the order of the others.
bool CancellationManager::CancelWaitingNR(int RID)
{
    Ticket* t = waitingNR->removeByID(RID);
    if (t == nullptr) return false;

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->enqueue(t);
    return true;
}

// NR that is already assigned but not finished yet: free the technician.
bool CancellationManager::CancelAssignedNR(int RID, int currentTime)
{
    Ticket* t = inService->getByID(RID);
    if (t == nullptr) return false;                  // finished or unknown id
    if (t->getType() != RequestType::NR) return false;   // SR / UR are ignored

    inService->removeByID(RID);

    for (int i = 0; i < technicianCount; i++)
    {
        Technician* tech = technicians[i];
        if (tech->getID() != t->getTID()) continue;

        // the technician was busy from AT until this cancellation minute
        tech->addBusyTime(currentTime - t->getAT());
        tech->releaseTicket();

        if (tech->getType() == TechnicianType::GT)
            availableGT->returnGT(tech);
        else
            availableST->returnST(tech);
        break;
    }

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->enqueue(t);
    return true;
}
