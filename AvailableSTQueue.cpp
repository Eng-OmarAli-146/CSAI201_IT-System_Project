#include "AvailableSTQueue.h"

AvailableSTQueue::AvailableSTQueue() : items(nullptr), count(0), capacity(0) {}

void AvailableSTQueue::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Technician** bigger = new Technician*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void AvailableSTQueue::siftUp(int index)
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

void AvailableSTQueue::siftDown(int index)
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

void AvailableSTQueue::insertST(Technician* t)
{
    if (count == capacity) grow();

    items[count] = t;
    siftUp(count);
    count++;
}

Technician* AvailableSTQueue::getST()
{
    if (count == 0) return nullptr;

    Technician* best = items[0];

    count--;
    items[0] = items[count];
    if (count > 0) siftDown(0);

    return best;
}

void AvailableSTQueue::returnST(Technician* t)
{
    insertST(t);
}

bool AvailableSTQueue::isEmpty() const { return count == 0; }

int AvailableSTQueue::getCount() const { return count; }
