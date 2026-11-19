#include "AvailableGTQueue.h"

void AvailableGTQueue::insertGT(Technician* t)
{
    std::list<Technician*>::iterator it = items.begin();
    while (it != items.end() && (*it)->getID() < t->getID())
        ++it;
    items.insert(it, t);
}

Technician* AvailableGTQueue::getGT()
{
    if (items.empty()) return nullptr;
    Technician* t = items.front();
    items.pop_front();
    return t;
}

void AvailableGTQueue::returnGT(Technician* t)
{
    insertGT(t);
}

bool AvailableGTQueue::isEmpty() { return items.empty(); }
