#include "AvailableGTQueue.h"

AvailableGTQueue::AvailableGTQueue() : items(nullptr), count(0), capacity(0) {}

void AvailableGTQueue::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Technician** bigger = new Technician*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void AvailableGTQueue::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (items[index]->getID() < items[parent]->getID())
        {
            Technician* temp = items[index];
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

void AvailableGTQueue::siftDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < count && items[left]->getID() < items[best]->getID()) best = left;
        if (right < count && items[right]->getID() < items[best]->getID()) best = right;
        if (best == index) break;

        Technician* temp = items[index];
        items[index] = items[best];
        items[best] = temp;
        index = best;
    }
}

void AvailableGTQueue::insertGT(Technician* t)
{
    if (count == capacity) grow();

    items[count] = t;
    siftUp(count);
    count++;
}

Technician* AvailableGTQueue::getGT()
{
    if (count == 0) return nullptr;

    Technician* best = items[0];

    count--;
    items[0] = items[count];
    if (count > 0) siftDown(0);

    return best;
}

void AvailableGTQueue::returnGT(Technician* t)
{
    insertGT(t);
}

bool AvailableGTQueue::isEmpty() const { return count == 0; }

int AvailableGTQueue::getCount() const { return count; }
