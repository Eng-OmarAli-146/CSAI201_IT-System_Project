#include "WaitingURPriorityQueue.h"
#include <iostream>

// Comparator: bigger PR first, then smaller QT, then smaller RID
bool WaitingURPriorityQueue::isBetter(Ticket* a, Ticket* b)
{
    if (a->getPR() != b->getPR())
        return a->getPR() > b->getPR();

    if (a->getQT() != b->getQT())
        return a->getQT() < b->getQT();

    return a->getRID() < b->getRID();
}

int WaitingURPriorityQueue::findHighestIndex()
{
    int best = 0;
    for (int i = 1; i < (int)items.size(); i++)
        if (isBetter(items[i], items[best]))
            best = i;
    return best;
}

void WaitingURPriorityQueue::insert(Ticket* t)
{
    items.push_back(t);
}

Ticket* WaitingURPriorityQueue::removeHighest()
{
    if (items.empty()) return nullptr;

    int best = findHighestIndex();
    Ticket* t = items[best];
    items.erase(items.begin() + best);
    return t;
}

Ticket* WaitingURPriorityQueue::peekHighest()
{
    if (items.empty()) return nullptr;
    return items[findHighestIndex()];
}

bool WaitingURPriorityQueue::isEmpty()  { return items.empty(); }
int  WaitingURPriorityQueue::getCount() { return items.size(); }

std::string WaitingURPriorityQueue::getIDs()
{
    // same order the scheduler would serve them in
    std::vector<Ticket*> remaining = items;
    std::string result;

    while (!remaining.empty())
    {
        int best = 0;
        for (int i = 1; i < (int)remaining.size(); i++)
            if (isBetter(remaining[i], remaining[best]))
                best = i;

        if (!result.empty()) result += " ";
        result += std::to_string(remaining[best]->getRID());
        remaining.erase(remaining.begin() + best);
    }
    return result;
}

void WaitingURPriorityQueue::print()
{
    for (size_t i = 0; i < items.size(); i++)
        std::cout << items[i]->getRID() << " ";
    std::cout << "\n";
}
