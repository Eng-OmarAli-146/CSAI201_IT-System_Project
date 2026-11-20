#pragma once
#include <list>
#include "Ticket.h"

// Always sorted by FT, then RID
class InServiceList
{
    std::list<Ticket*> items;

public:
    void    insert(Ticket* t);
    Ticket* removeFirst();
    Ticket* peek();
    Ticket* getByID(int RID);      // nullptr if not found
    Ticket* removeByID(int RID);   // nullptr if not found
    bool    isEmpty();
    void    print();
};
