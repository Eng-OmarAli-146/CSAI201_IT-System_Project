#pragma once
#include "Ticket.h"

// Hand-written linked FIFO queue for the specialist requests (SR).
class WaitingSRQueue
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
    WaitingSRQueue();

    void    enqueue(Ticket* t);
    Ticket* dequeue();
    Ticket* peek() const;
    bool    isEmpty() const;
    int     getCount() const;
    void    printIDs() const;
};
