#include "ProblemConfigurationQueue.h"

ProblemConfigurationQueue::ProblemConfigurationQueue()
    : head(nullptr), tail(nullptr), count(0) {}

void ProblemConfigurationQueue::insertConfiguration(const ServiceConfiguration& configuration)
{
    Node* node = new Node;
    node->data = configuration;
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

const ServiceConfiguration* ProblemConfigurationQueue::getConfigurationByPC(int pc) const
{
    Node* current = head;
    int position = 1;

    while (current != nullptr)
    {
        if (position == pc) return &current->data;
        current = current->next;
        position++;
    }
    return nullptr;
}

int ProblemConfigurationQueue::getDuration(int pc) const
{
    const ServiceConfiguration* configuration = getConfigurationByPC(pc);
    if (configuration == nullptr) return 0;
    return configuration->getDuration();
}

std::string ProblemConfigurationQueue::getCategory(int pc) const
{
    const ServiceConfiguration* configuration = getConfigurationByPC(pc);
    if (configuration == nullptr) return std::string("");
    return configuration->getCategory();
}

int ProblemConfigurationQueue::size() const { return count; }
