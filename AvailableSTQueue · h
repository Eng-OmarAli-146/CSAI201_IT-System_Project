#pragma once
#include <list>
#include "Technician.h"

// Always sorted by smallest ID first
class AvailableSTQueue
{
    std::list<Technician*> items;

public:
    void        insertST(Technician* t);
    Technician* getST();               // takes the smallest ID
    void        returnST(Technician* t);
    bool        isEmpty();
};
