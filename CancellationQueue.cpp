#include "CancellationQueue.h"

CancellationQueue::CancellationQueue() : head(nullptr), tail(nullptr), count(0) {}

void CancellationQueue::enqueue(const CancellationRequest& request)
{
    Node* node = new Node;
    node->data = request;
    node->next = nullptr;

    if (tail == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    count++;
}

bool CancellationQueue::isEmpty() const { return count == 0; }

int CancellationQueue::getCount() const { return count; }

CancellationRequest* CancellationQueue::toArray(int& size) const
{
    CancellationRequest* items = new CancellationRequest[count > 0 ? count : 1];

    int i = 0;
    Node* current = head;
    while (current != nullptr)
    {
        items[i] = current->data;
        i++;
        current = current->next;
    }

    size = count;
    return items;
}
