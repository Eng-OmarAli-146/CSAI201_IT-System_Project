#pragma once
#include "Technician.h"

// Hand-written array based min-heap of the available specialist technicians.
// The smallest technician ID is always on top.
class AvailableSTQueue
{
private:
    Technician** items;
    int count;
    int capacity;

    void grow();
    void siftUp(int index);
    void siftDown(int index);

public:
    AvailableSTQueue();

    void        insertST(Technician* t);
    Technician* getST();               // takes the smallest ID
    void        returnST(Technician* t);
    bool        isEmpty() const;
    int         getCount() const;
};
