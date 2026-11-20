#include "InServiceList.h"
#include <iostream>

InServiceList::InServiceList() : items(nullptr), count(0), capacity(0) {}

// Order: smaller FT first, then smaller RID
bool InServiceList::isBefore(Ticket* a, Ticket* b) const
{
    if (a->getFT() != b->getFT())
        return a->getFT() < b->getFT();

    return a->getRID() < b->getRID();
}

void InServiceList::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Ticket** bigger = new Ticket*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void InServiceList::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (isBefore(items[index], items[parent]))
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

void InServiceList::siftDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < count && isBefore(items[left], items[best])) best = left;
        if (right < count && isBefore(items[right], items[best])) best = right;
        if (best == index) break;

        Ticket* temp = items[index];
        items[index] = items[best];
        items[best] = temp;
        index = best;
    }
}

int InServiceList::findIndex(int RID) const
{
    for (int i = 0; i < count; i++)
        if (items[i]->getRID() == RID) return i;

    return -1;
}

void InServiceList::insert(Ticket* t)
{
    if (count == capacity) grow();

    items[count] = t;
    siftUp(count);
    count++;
}

Ticket* InServiceList::removeFirst()
{
    if (count == 0) return nullptr;

    Ticket* first = items[0];

    count--;
    items[0] = items[count];
    if (count > 0) siftDown(0);

    return first;
}

Ticket* InServiceList::peek() const
{
    if (count == 0) return nullptr;
    return items[0];
}

Ticket* InServiceList::getByID(int RID) const
{
    int index = findIndex(RID);
    if (index < 0) return nullptr;
    return items[index];
}

Ticket* InServiceList::removeByID(int RID)
{
    int index = findIndex(RID);
    if (index < 0) return nullptr;

    Ticket* removed = items[index];

    count--;
    items[index] = items[count];

    if (index < count)
    {
        siftUp(index);      // the moved ticket may belong higher ...
        siftDown(index);    // ... or lower in the heap
    }

    return removed;
}

bool InServiceList::isEmpty() const { return count == 0; }

int InServiceList::getCount() const { return count; }

void InServiceList::printIDs() const
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
            if (isBefore(copy[i], copy[best])) best = i;

        std::cout << copy[best]->getRID();
        if (remaining > 1) std::cout << " ";

        copy[best] = copy[remaining - 1];
        remaining--;
    }

    delete[] copy;
    std::cout << "\n";
}
