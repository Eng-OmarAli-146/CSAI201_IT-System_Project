#pragma once
#include "Ticket.h"

// Hand-written linked FIFO queue for the normal requests (NR).
// removeByID keeps the order of the other tickets unchanged.
class WaitingNRQueue
{
private:
    struct Node
    {
        Ticket* data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    WaitingNRQueue();

    void    enqueue(Ticket* t);
    Ticket* dequeue();
    Ticket* peek() const;
    Ticket* removeByID(int RID);   // nullptr if not found
    bool    isEmpty() const;
    int     getCount() const;
    void    printIDs() const;
};
