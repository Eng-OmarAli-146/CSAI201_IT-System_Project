#pragma once
#include "Definitions.h"

// Hand-written linked FIFO queue of cancellation records.
class CancellationQueue
{
private:
    struct Node
    {
        CancellationRequest data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    CancellationQueue();

    void    enqueue(const CancellationRequest& request);
    bool    isEmpty() const;
    int     getCount() const;

    // copies the records into a new array (the caller owns the array)
    CancellationRequest* toArray(int& size) const;
};
