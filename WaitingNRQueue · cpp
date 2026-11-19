#include "WaitingNRQueue.h"
#include <iostream>

void WaitingNRQueue::enqueue(Ticket* t)
{
    items.push_back(t);
}

Ticket* WaitingNRQueue::dequeue()
{
    if (items.empty()) return nullptr;
    Ticket* t = items.front();
    items.pop_front();
    return t;
}

Ticket* WaitingNRQueue::peek()
{
    if (items.empty()) return nullptr;
    return items.front();
}

Ticket* WaitingNRQueue::removeByID(int RID)
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

bool WaitingNRQueue::isEmpty()  { return items.empty(); }
int  WaitingNRQueue::getCount() { return items.size(); }

void WaitingNRQueue::print()
{
    for (std::list<Ticket*>::iterator it = items.begin(); it != items.end(); ++it)
        std::cout << (*it)->getRID() << " ";
    std::cout << "\n";
}
