#include "WaitingURPriorityQueue.h"
#include <iostream>

WaitingURPriorityQueue::WaitingURPriorityQueue()
    : items(nullptr), count(0), capacity(0) {}

// Comparator: bigger PR first, then smaller QT, then smaller RID
bool WaitingURPriorityQueue::isBetter(Ticket* a, Ticket* b) const
{
    if (a->getPR() != b->getPR())
        return a->getPR() > b->getPR();

    if (a->getQT() != b->getQT())
        return a->getQT() < b->getQT();

    return a->getRID() < b->getRID();
}

void WaitingURPriorityQueue::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Ticket** bigger = new Ticket*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void WaitingURPriorityQueue::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (isBetter(items[index], items[parent]))
        {
            Ticket* temp = items[index];
            items[index] = items[parent];
            items[parent] = temp;
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void WaitingURPriorityQueue::siftDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < count && isBetter(items[left], items[best])) best = left;
        if (right < count && isBetter(items[right], items[best])) best = right;
        if (best == index) break;

        Ticket* temp = items[index];
        items[index] = items[best];
        items[best] = temp;
        index = best;
    }
}

void WaitingURPriorityQueue::insert(Ticket* t)
{
    if (count == capacity) grow();

    items[count] = t;
    siftUp(count);
    count++;
}

Ticket* WaitingURPriorityQueue::removeHighest()
{
    if (count == 0) return nullptr;

    Ticket* best = items[0];

    count--;
    items[0] = items[count];
    if (count > 0) siftDown(0);

    return best;
}

Ticket* WaitingURPriorityQueue::peekHighest() const
{
    if (count == 0) return nullptr;
    return items[0];
}

bool WaitingURPriorityQueue::isEmpty() const { return count == 0; }

int WaitingURPriorityQueue::getCount() const { return count; }

void WaitingURPriorityQueue::printIDs()
{
    if (count == 0)
    {
        std::cout << "-\n";
        return;
    }

    // work on a copy so the real heap does not change
    Ticket** copy = new Ticket*[count];
    for (int i = 0; i < count; i++)
        copy[i] = items[i];

    int remaining = count;
    while (remaining > 0)
    {
        int best = 0;
        for (int i = 1; i < remaining; i++)
            if (isBetter(copy[i], copy[best])) best = i;

        std::cout << copy[best]->getRID();
        if (remaining > 1) std::cout << " ";

        copy[best] = copy[remaining - 1];
        remaining--;
    }

    delete[] copy;
    std::cout << "\n";
}
