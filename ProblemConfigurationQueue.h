#pragma once
#include <string>
#include "ServiceConfiguration.h"

// Hand-written linked FIFO queue of service configurations.
// Problem code "pc" is the position of the configuration in this list (1, 2, 3, ...).
class ProblemConfigurationQueue
{
private:
    struct Node
    {
        ServiceConfiguration data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    ProblemConfigurationQueue();

    void insertConfiguration(const ServiceConfiguration& configuration);
    const ServiceConfiguration* getConfigurationByPC(int pc) const;
    int getDuration(int pc) const;
    std::string getCategory(int pc) const;
    int size() const;
};
