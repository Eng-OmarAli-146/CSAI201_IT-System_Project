#pragma once
#include "Ticket.h"

// Hand-written array based min-heap of the tickets being served.
// The first ticket to finish is the one with the smaller FT
// (and the smaller RID when the FT is equal).
class InServiceList
{
private:
    Ticket** items;
    int count;
    int capacity;

    bool isBefore(Ticket* a, Ticket* b) const;   // true if a finishes first
    void grow();
    void siftUp(int index);
    void siftDown(int index);
    int  findIndex(int RID) const;

public:
    InServiceList();

    void    insert(Ticket* t);
    Ticket* removeFirst();
    Ticket* peek() const;
    Ticket* getByID(int RID) const;   // nullptr if not in service
    Ticket* removeByID(int RID);      // nullptr if not in service
    bool    isEmpty() const;
    int     getCount() const;
    void    printIDs() const;
};
