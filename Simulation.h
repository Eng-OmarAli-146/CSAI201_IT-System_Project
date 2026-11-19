#pragma once
#include <vector>
#include "Definitions.h"
#include "Ticket.h"
#include "Technician.h"
#include "CancellationManager.h"
#include "WaitingNRQueue.h"
#include "WaitingSRQueue.h"
#include "WaitingURPriorityQueue.h"
#include "InServiceList.h"
#include "AvailableGTQueue.h"
#include "AvailableSTQueue.h"
#include "ProblemConfigurationQueue.h"
#include "Scheduler.h"

class Simulation
{
    int CurrentTime;
    int Mode;                       // 1 = Interactive, 2 = Silent

    // from InputReader
    std::vector<Ticket*>             allRequests;
    std::vector<CancellationRequest> allCancellations;
    std::vector<Technician*>         technicians;
    size_t nextRequest;
    size_t nextCancel;

    // structures (declaration order matters: used by the two objects below)
    WaitingNRQueue         waitingNR;
    WaitingSRQueue         waitingSR;
    WaitingURPriorityQueue waitingUR;
    InServiceList          inService;
    AvailableGTQueue       availableGT;
    AvailableSTQueue       availableST;
    std::vector<Ticket*>   completed;
    std::vector<Ticket*>   cancelled;

    Scheduler           scheduler;
    CancellationManager cancelManager;

public:
    Simulation(std::vector<Ticket*> requests,
               std::vector<CancellationRequest> cancellations,
               std::vector<Technician*> techs,
               ProblemConfigurationQueue* configs,
               int mode);

    void Run();
    void CompleteServices();
    void ReleaseRequests();
    void ProcessCancellation();
    void Display();
    bool Finished();
};
