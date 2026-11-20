#include "WaitingNRQueue.h"
#include <iostream>

WaitingNRQueue::WaitingNRQueue() : head(nullptr), tail(nullptr), count(0) {}

void WaitingNRQueue::enqueue(Ticket* t)
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

Ticket* WaitingNRQueue::dequeue()
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

Ticket* WaitingNRQueue::peek() const
{
    if (head == nullptr) return nullptr;
    return head->data;
}

Ticket* WaitingNRQueue::removeByID(int RID)
{
    Node* previous = nullptr;
    Node* current = head;

    while (current != nullptr)
    {
        if (current->data->getRID() == RID)
        {
            Ticket* found = current->data;

            if (previous == nullptr) head = current->next;
            else                     previous->next = current->next;

            if (current == tail) tail = previous;

            delete current;
            count--;
            return found;
        }
        previous = current;
        current = current->next;
    }
    return nullptr;
}

bool WaitingNRQueue::isEmpty() const { return count == 0; }

int WaitingNRQueue::getCount() const { return count; }

void WaitingNRQueue::printIDs() const
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
