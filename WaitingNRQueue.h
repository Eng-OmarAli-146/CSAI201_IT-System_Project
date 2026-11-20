#pragma once
#include <list>
#include <string>
#include "Ticket.h"

class WaitingNRQueue
{
    std::list<Ticket*> items;

public:
    void    enqueue(Ticket* t);
    Ticket* dequeue();
    Ticket* peek();
    Ticket* removeByID(int RID);   // nullptr if not found
    bool    isEmpty();
    int     getCount();
    void    print();
    std::string getIDs();          // ticket IDs in scheduling order
};
