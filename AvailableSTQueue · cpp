#include "AvailableSTQueue.h"

void AvailableSTQueue::insertST(Technician* t)
{
    std::list<Technician*>::iterator it = items.begin();
    while (it != items.end() && (*it)->getID() < t->getID())
        ++it;
    items.insert(it, t);
}

Technician* AvailableSTQueue::getST()
{
    if (items.empty()) return nullptr;
    Technician* t = items.front();
    items.pop_front();
    return t;
}

void AvailableSTQueue::returnST(Technician* t)
{
    insertST(t);
}

bool AvailableSTQueue::isEmpty() { return items.empty(); }
