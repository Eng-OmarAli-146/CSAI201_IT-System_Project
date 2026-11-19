#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <iostream>
#include <vector>
#include "Ticket.h"
#include "Technician.h"
#include "Definitions.h"
using namespace std;
class TicketNode
{
public:
    Ticket* data;
    TicketNode* next;
    TicketNode(Ticket* ticket);
};
class TicketQueue
{
private:
    TicketNode* front;
    TicketNode* rear;
    int count;
public:
    TicketQueue();
    ~TicketQueue();
    TicketQueue(const TicketQueue&) = delete;
    TicketQueue& operator=(const TicketQueue&) = delete;
    bool contains(int id) const;
    Ticket* enqueue(Ticket* ticket);
    Ticket* dequeue();
    Ticket* peek() const;
    Ticket* removeByID(int id);
    bool isEmpty() const;
    int getCount() const;
    void clear();
};
class WaitingNRQueue
{
private:
    TicketQueue queue;
public:
    Ticket* enqueue(Ticket* ticket);
    Ticket* dequeue();
    Ticket* peek();
    Ticket* removeByID(int id);
    bool isEmpty() const;
    int getCount() const;
    void clear();
};
class WaitingSRQueue
{
private:
    TicketQueue queue;
public:
    Ticket* enqueue(Ticket* ticket);
    Ticket* dequeue();
    Ticket* peek();
    Ticket* removeByID(int id);
    bool isEmpty() const;
    int getCount() const;
    void clear();
};
template <class T>
class PriorityNode
{
public:
    T* data;
    PriorityNode* next;
    PriorityNode(T* value);
};
template <class T>
class LinkedPriorityQueue
{
private:
    PriorityNode<T>* front;
    int count;
    bool (*higherPriority)(T*, T*);
    int (*getID)(T*);
public:
    LinkedPriorityQueue(
        bool (*compare)(T*, T*),
        int (*identifier)(T*)
    );
    ~LinkedPriorityQueue();
    LinkedPriorityQueue(const LinkedPriorityQueue&) = delete;
    LinkedPriorityQueue& operator=(const LinkedPriorityQueue&) = delete;
    bool contains(int id) const;
    T* insert(T* value);
    T* peek() const;
    T* extract();
    T* removeByID(int id);
    bool isEmpty() const;
    int getCount() const;
    void clear();
};
bool higherURPriority(T* first, T* second);
bool earlierFinish(T* first, T* second);
bool smallerTechnicianID(
    Technician* first,
    Technician* second
);
int getTicketRID(Ticket* ticket);
int getTechnicianID(Technician* technician);
class WaitingURPriorityQueue
{
private:
    LinkedPriorityQueue<Ticket> queue;
public:
    WaitingURPriorityQueue();
    Ticket* insert(Ticket* ticket);
    Ticket* removeHighest();
    Ticket* peekHighest();
    Ticket* removeByID(int id);
    bool isEmpty() const;
    int getCount() const;
    void clear();
};
class InServiceQueue
{
private:
    LinkedPriorityQueue<Ticket> queue;
public:
    InServiceQueue();
    Ticket* insert(Ticket* ticket);
    Ticket* extractMin();
    Ticket* peek();
    Ticket* removeByID(int id);
    bool isEmpty() const;
    int getCount() const;
    void clear();
};
class AvailableGTQueue
{
private:
    LinkedPriorityQueue<Technician> queue;
public:
    AvailableGTQueue();
    Technician* insertGT(Technician* technician);
    Technician* getGT();
    Technician* returnGT(Technician* technician);
    bool isEmpty() const;
    bool contains(int id) const;
    void clear();
};
class AvailableSTQueue
{
private:
    LinkedPriorityQueue<Technician> queue;
public:
    AvailableSTQueue();
    Technician* insertST(Technician* technician);
    Technician* getST();
    Technician* returnST(Technician* technician);
    bool isEmpty() const;
    bool contains(int id) const;
    void clear();
};
class TechnicianAvailability
{
private:
    AvailableGTQueue gtQueue;
    AvailableSTQueue stQueue;
public:
    Technician* addGT(Technician* technician);
    Technician* addST(Technician* technician);
    Technician* getAvailableGT();
    Technician* getAvailableST();
    Technician* returnGT(Technician* technician);
    Technician* returnST(Technician* technician);
    bool hasAvailableGT() const;
    bool hasAvailableST() const;
    void clear();
};
class Scheduler
{
private:
    WaitingNRQueue* nrQueue;
    WaitingSRQueue* srQueue;
    WaitingURPriorityQueue* urQueue;
    InServiceQueue* inServiceQueue;
    TechnicianAvailability* technicians;
    int currentTime;
    int (*durationProvider)(int);
    struct Assignment
    {
        Ticket* ticket;
        Technician* technician;
        bool isGT;
    };
    vector<Assignment> assignments;
    Ticket* AssignUR();
    Ticket* AssignSR();
    Ticket* AssignNR();
    Ticket* AssignTicket(
        Ticket* ticket,
        Technician* technician,
        bool isGT
    );
public:
    Scheduler(
        WaitingNRQueue* nr,
        WaitingSRQueue* sr,
        WaitingURPriorityQueue* ur,
        InServiceQueue* inService,
        TechnicianAvailability* available,
        int time,
        int (*getDuration)(int)
    );
    vector<Ticket*> AssignTickets();
    Ticket* AssignUR();
    Ticket* AssignSR();
    Ticket* AssignNR();
    Ticket* AssignTicket(
        Ticket* ticket,
        Technician* technician,
        bool isGT
    );
    Ticket* CompleteService();
    void setCurrentTime(int time);
    int getCurrentTime() const;
};

#endif
