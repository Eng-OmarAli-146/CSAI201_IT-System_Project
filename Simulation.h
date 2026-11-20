#pragma once
#include <string>
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
#include "LocationManager.h"
#include "TicketQueue.h"
#include "Scheduler.h"

class Simulation
{
    int  CurrentTime;
    bool interactive;                       // true = Interactive, false = Silent
    const ProblemConfigurationQueue* configs;
    const LocationManager*           locations;
    std::string outputFileName;

    // data received from the InputReader
    Ticket**              allRequests;
    int                   requestCount;
    int                   nextRequest;
    CancellationRequest*  allCancellations;
    int                   cancellationCount;
    int                   nextCancel;
    Technician**          technicians;
    int                   technicianCount;
    int                   stCount;
    int                   gtCount;

    // structures (declaration order matters: used by the two objects below)
    WaitingNRQueue         waitingNR;
    WaitingSRQueue         waitingSR;
    WaitingURPriorityQueue waitingUR;
    InServiceList          inService;
    AvailableGTQueue       availableGT;
    AvailableSTQueue       availableST;
    TicketQueue            completed;
    TicketQueue            cancelled;

    Scheduler           scheduler;
    CancellationManager cancelManager;

    bool CannotBeServed();

public:
    Simulation(Ticket** requests, int requestCount,
               CancellationRequest* cancellations, int cancellationCount,
               Technician** techs, int technicianCount,
               const ProblemConfigurationQueue* configs,
               const LocationManager* locations,
               bool interactive,
               const std::string& outputFileName);

    ~Simulation();

    void Run();
    void CompleteServices();
    void ReleaseRequests();
    void ProcessCancellation();
    void Display();
    bool Finished();
};
