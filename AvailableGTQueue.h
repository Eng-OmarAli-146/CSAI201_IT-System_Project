#pragma once
#include "Technician.h"

// Hand-written array based min-heap of the available general technicians.
// The smallest technician ID is always on top.
class AvailableGTQueue
{
private:
    Technician** items;
    int count;
    int capacity;

    void grow();
    void siftUp(int index);
    void siftDown(int index);

public:
    AvailableGTQueue();

    void        insertGT(Technician* t);
    Technician* getGT();               // takes the smallest ID
    void        returnGT(Technician* t);
    bool        isEmpty() const;
    int         getCount() const;
};
