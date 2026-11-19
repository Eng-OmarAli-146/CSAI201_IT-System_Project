#pragma once
#include <vector>
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
};
