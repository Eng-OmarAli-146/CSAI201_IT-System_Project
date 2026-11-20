#include "CancellationManager.h"

// Only NR tickets may be cancelled; unknown IDs, completed, cancelled,
// SR and UR tickets are ignored (handled by the two checks below).
bool CancellationManager::CancelTicket(int RID, int currentTime)
{
    if (CancelWaitingNR(RID))
        return true;
    return CancelAssignedNR(RID, currentTime);   // else: ignore
}

bool CancellationManager::CancelWaitingNR(int RID)
{
    Ticket* t = waitingNR->removeByID(RID);
    if (!t) return false;

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->push_back(t);
    return true;
}

bool CancellationManager::CancelAssignedNR(int RID, int currentTime)
{
    Ticket* t = inService->getByID(RID);
    if (!t) return false;                            // finished or unknown
    if (t->getType() != RequestType::NR) return false;  // SR / UR are ignored

    inService->removeByID(RID);

    for (std::size_t i = 0; i < technicians->size(); i++)
    {
        Technician* tech = (*technicians)[i];
        if (tech->getID() == t->getTID())
        {
            // busy interval runs from AT until the technician is released
            tech->addBusyTime(currentTime - t->getAT());
            tech->releaseTicket();
            if (tech->getType() == TechnicianType::GT)
                availableGT->returnGT(tech);
            else
                availableST->returnST(tech);
            break;
        }
    }

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->push_back(t);
    return true;
}
