#include "TicketQueue.h"
#include <iostream>

TicketQueue::TicketQueue() : head(nullptr), tail(nullptr), count(0) {}

void TicketQueue::enqueue(Ticket* t)
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

Ticket* TicketQueue::dequeue()
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

Ticket* TicketQueue::peek() const
{
    if (head == nullptr) return nullptr;
    return head->data;
}

Ticket* TicketQueue::removeByID(int RID)
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

bool TicketQueue::isEmpty() const { return count == 0; }

int TicketQueue::getCount() const { return count; }

void TicketQueue::printIDs() const
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

Ticket** TicketQueue::toArray(int& size) const
{
    Ticket** items = new Ticket*[count > 0 ? count : 1];

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
