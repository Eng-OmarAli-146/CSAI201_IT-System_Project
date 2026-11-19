#pragma once
#include "Definitions.h"
#include "Ticket.h"
#include "Technician.h"
#include "WaitingNRQueue.h"
#include "WaitingSRQueue.h"
#include "WaitingURPriorityQueue.h"
#include "InServiceList.h"
#include "AvailableGTQueue.h"
#include "AvailableSTQueue.h"
#include "ProblemConfigurationQueue.h"

class Scheduler
{
    WaitingNRQueue*            waitingNR;
    WaitingSRQueue*            waitingSR;
    WaitingURPriorityQueue*    waitingUR;
    InServiceList*             inService;
    AvailableGTQueue*          availableGT;
    AvailableSTQueue*          availableST;
    ProblemConfigurationQueue* configs;

public:
    Scheduler(WaitingNRQueue* nr, WaitingSRQueue* sr, WaitingURPriorityQueue* ur,
              InServiceList* srv, AvailableGTQueue* gt, AvailableSTQueue* st,
              ProblemConfigurationQueue* cfg)
        : waitingNR(nr), waitingSR(sr), waitingUR(ur), inService(srv),
          availableGT(gt), availableST(st), configs(cfg) {}

    void AssignTickets(int currentTime);
    void AssignUR(int currentTime);
    void AssignSR(int currentTime);
    void AssignNR(int currentTime);
    void AssignTicket(Ticket* t, Technician* tech, int currentTime);
};
