#include "WaitingSRQueue.h"
#include <iostream>

WaitingSRQueue::WaitingSRQueue() : head(nullptr), tail(nullptr), count(0) {}

void WaitingSRQueue::enqueue(Ticket* t)
{
    Node* node = new Node;
    node->data = t;
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

Ticket* WaitingSRQueue::dequeue()
{
    if (head == nullptr) return nullptr;

    Node* node = head;
    Ticket* t = node->data;

    head = head->next;
    if (head == nullptr) tail = nullptr;

    delete node;
    count--;
    return t;
}

Ticket* WaitingSRQueue::peek() const
{
    if (head == nullptr) return nullptr;
    return head->data;
}

bool WaitingSRQueue::isEmpty() const { return count == 0; }

int WaitingSRQueue::getCount() const { return count; }

void WaitingSRQueue::printIDs() const
{
    if (head == nullptr)
    {
        std::cout << "-\n";
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        std::cout << current->data->getRID();
        if (current->next != nullptr) std::cout << " ";
        current = current->next;
    }
    std::cout << "\n";
}
