#pragma once
#include "Ticket.h"

// Hand-written linked FIFO queue of ticket pointers.
// It is used for AllRequests, Completed and Cancelled, which are all
// simple first-in first-out lists of tickets.
class TicketQueue
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
    TicketQueue();

    void    enqueue(Ticket* t);      // add at the back (FIFO)
    Ticket* dequeue();               // remove from the front
    Ticket* peek() const;            // front ticket without removing it
    Ticket* removeByID(int RID);     // nullptr if not found
    bool    isEmpty() const;
    int     getCount() const;
    void    printIDs() const;        // prints the ticket ids, "-" if empty

    // copies the tickets into a new array (the caller owns the array)
    Ticket** toArray(int& size) const;
};
