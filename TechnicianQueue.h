#pragma once
#include "Technician.h"

// Hand-written linked FIFO queue of the technicians of the IT unit.
class TechnicianQueue
{
private:
    struct Node
    {
        Technician data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    TechnicianQueue();

    void        insertTechnician(const Technician& technician);
    Technician* getTechnicianByID(int id);
    bool        updateTechnician(int id, const Technician& technician);
    void        printWorkingTechnicians() const;
    int         size() const;

    // copies pointers to the technicians into a new array (the caller owns it)
    Technician** toArray(int& size);
};
