#include "CancellationManager.h"

bool CancellationManager::CancelTicket(int RID)
{
    if (CancelWaitingNR(RID))
        return true;
    return CancelAssignedNR(RID);   // else: ignore
}

bool CancellationManager::CancelWaitingNR(int RID)
{
    Ticket* t = waitingNR->removeByID(RID);
    if (!t) return false;

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->push_back(t);
    return true;
}

bool CancellationManager::CancelAssignedNR(int RID)
{
    Ticket* t = inService->removeByID(RID);
    if (!t) return false;

    for (std::size_t i = 0; i < technicians->size(); i++)
    {
        Technician* tech = (*technicians)[i];
        if (tech->getID() == t->getTID())
        {
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
