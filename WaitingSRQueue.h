#pragma once
#include <queue>
#include <string>
#include "Ticket.h"

class WaitingSRQueue
{
    std::queue<Ticket*> items;

public:
    void    enqueue(Ticket* t);
    Ticket* dequeue();
    Ticket* peek();
    bool    isEmpty();
    int     getCount();
    void    print();
    std::string getIDs();          // ticket IDs in scheduling order
};
