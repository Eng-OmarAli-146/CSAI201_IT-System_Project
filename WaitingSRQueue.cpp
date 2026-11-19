#include "WaitingSRQueue.h"
#include <iostream>

void WaitingSRQueue::enqueue(Ticket* t)
{
    items.push(t);
}

Ticket* WaitingSRQueue::dequeue()
{
    if (items.empty()) return nullptr;
    Ticket* t = items.front();
    items.pop();
    return t;
}

Ticket* WaitingSRQueue::peek()
{
    if (items.empty()) return nullptr;
    return items.front();
}

bool WaitingSRQueue::isEmpty()  { return items.empty(); }
int  WaitingSRQueue::getCount() { return items.size(); }

void WaitingSRQueue::print()
{
    // a std::queue can't be looped over, so we copy it first
    std::queue<Ticket*> copy = items;
    while (!copy.empty())
    {
        std::cout << copy.front()->getRID() << " ";
        copy.pop();
    }
    std::cout << "\n";
}
