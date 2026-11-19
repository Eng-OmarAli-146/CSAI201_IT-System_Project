#pragma once
#include <list>
#include "Technician.h"

// Always sorted by smallest ID first
class AvailableGTQueue
{
    std::list<Technician*> items;

public:
    void        insertGT(Technician* t);
    Technician* getGT();               // takes the smallest ID
    void        returnGT(Technician* t);
    bool        isEmpty();
};
