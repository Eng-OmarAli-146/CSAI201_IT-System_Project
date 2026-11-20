#pragma once
#include "Ticket.h"

// Hand-written array based max-heap for the urgent requests (UR).
// The "largest" ticket is the one that must be served first:
//   higher PR first, then smaller QT, then smaller RID.
class WaitingURPriorityQueue
{
private:
    Ticket** items;    // the heap is stored in this dynamic array
    int count;
    int capacity;

    bool isBetter(Ticket* a, Ticket* b) const;   // true if a must be served before b
    void grow();
    void siftUp(int index);
    void siftDown(int index);

public:
    WaitingURPriorityQueue();

    void    insert(Ticket* t);
    Ticket* removeHighest();
    Ticket* peekHighest() const;
    bool    isEmpty() const;
    int     getCount() const;
    void    printIDs();          // prints ids in scheduling order
};
