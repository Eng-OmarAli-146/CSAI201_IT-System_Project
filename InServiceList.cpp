#include "InServiceList.h"
#include <iostream>

void InServiceList::insert(Ticket* t)
{
    std::list<Ticket*>::iterator it = items.begin();

    // move forward until we find the first ticket that must come AFTER t
    while (it != items.end())
    {
        if (t->getFT() < (*it)->getFT())
            break;
        if (t->getFT() == (*it)->getFT() && t->getRID() < (*it)->getRID())
            break;
        ++it;
    }
    items.insert(it, t);
}

Ticket* InServiceList::removeFirst()
{
    if (items.empty()) return nullptr;
    Ticket* t = items.front();
    items.pop_front();
    return t;
}

Ticket* InServiceList::peek()
{
    if (items.empty()) return nullptr;
    return items.front();
}

Ticket* InServiceList::removeByID(int RID)
{
    for (std::list<Ticket*>::iterator it = items.begin(); it != items.end(); ++it)
    {
        if ((*it)->getRID() == RID)
        {
            Ticket* t = *it;
            items.erase(it);
            return t;
        }
    }
    return nullptr;
}

bool InServiceList::isEmpty() { return items.empty(); }

void InServiceList::print()
{
    for (std::list<Ticket*>::iterator it = items.begin(); it != items.end(); ++it)
        std::cout << (*it)->getRID() << " ";
    std::cout << "\n";
}
