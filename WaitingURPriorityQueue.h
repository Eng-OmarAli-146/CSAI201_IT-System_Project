#pragma once
#include <vector>
#include <string>
#include "Ticket.h"

class WaitingURPriorityQueue
{
    std::vector<Ticket*> items;

    bool isBetter(Ticket* a, Ticket* b);   // true if a must be served before b
    int  findHighestIndex();

public:
    void    insert(Ticket* t);
    Ticket* removeHighest();
    Ticket* peekHighest();
    bool    isEmpty();
    int     getCount();
    void    print();
    std::string getIDs();          // ticket IDs in scheduling order
};
