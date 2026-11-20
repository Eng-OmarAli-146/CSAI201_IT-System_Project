#include "TechnicianQueue.h"
#include <iostream>

TechnicianQueue::TechnicianQueue() : head(nullptr), tail(nullptr), count(0) {}

void TechnicianQueue::insertTechnician(const Technician& technician)
{
    Node* node = new Node;
    node->data = technician;
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

Technician* TechnicianQueue::getTechnicianByID(int id)
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->data.getID() == id) return &current->data;
        current = current->next;
    }
    return nullptr;
}

bool TechnicianQueue::updateTechnician(int id, const Technician& technician)
{
    Technician* found = getTechnicianByID(id);
    if (found == nullptr) return false;

    *found = technician;
    return true;
}

void TechnicianQueue::printWorkingTechnicians() const
{
    Node* current = head;
    while (current != nullptr)
    {
        if (!current->data.isAvailable())
            std::cout << "Technician " << current->data.getID() << " is working\n";
        current = current->next;
    }
}

int TechnicianQueue::size() const { return count; }

Technician** TechnicianQueue::toArray(int& size)
{
    Technician** items = new Technician*[count > 0 ? count : 1];

    int i = 0;
    Node* current = head;
    while (current != nullptr)
    {
        items[i] = &current->data;
        i++;
        current = current->next;
    }

    size = count;
    return items;
}
