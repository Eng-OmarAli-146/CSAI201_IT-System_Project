#include "Simulation.h"
#include "Statistics.h"
#include "OutputWriter.h"
#include <iostream>

// short text used by the interactive display
static const char* RequestTypeName(RequestType type)
{
    if (type == RequestType::NR) return "NR";
    if (type == RequestType::SR) return "SR";
    return "UR";
}

static const char* TechnicianTypeName(TechnicianType type)
{
    if (type == TechnicianType::ST) return "ST";
    return "GT";
}

Simulation::Simulation(Ticket** requests, int requestCount,
                       CancellationRequest* cancellations, int cancellationCount,
                       Technician** techs, int technicianCount,
                       const ProblemConfigurationQueue* configs,
                       const LocationManager* locations,
                       bool interactive,
                       const std::string& outputFileName)
    : CurrentTime(1), interactive(interactive), configs(configs), locations(locations),
      outputFileName(outputFileName),
      allRequests(requests), requestCount(requestCount), nextRequest(0),
      allCancellations(cancellations), cancellationCount(cancellationCount), nextCancel(0),
      technicians(techs), technicianCount(technicianCount), stCount(0), gtCount(0),
      scheduler(&waitingNR, &waitingSR, &waitingUR, &inService,
                &availableGT, &availableST, configs),
      cancelManager(&waitingNR, &inService, &availableGT, &availableST,
                    technicians, technicianCount, &cancelled)
{
    // put every technician in the available heap that matches its type
    for (int i = 0; i < technicianCount; i++)
    {
        if (technicians[i]->getType() == TechnicianType::GT)
        {
            availableGT.insertGT(technicians[i]);
            gtCount++;
        }
        else
        {
            availableST.insertST(technicians[i]);
            stCount++;
        }
    }
}

Simulation::~Simulation()
{
    delete[] allRequests;
    delete[] allCancellations;
    delete[] technicians;
}

void Simulation::Run()
{
    if (!interactive)
    {
        std::cout << "Silent Mode\n";
        std::cout << "Simulation Starts...\n";
    }

    bool stopped = false;

    while (!Finished())
    {
        CompleteServices();
        ReleaseRequests();
        ProcessCancellation();
        scheduler.AssignTickets(CurrentTime);
        Display();

        // safety: a waiting ticket that has no technician type at all
        // in the system can never be served, so we must not loop forever
        if (CannotBeServed())
        {
            std::cout << "\nWarning: no suitable technician exists for a waiting ticket, "
                         "so the simulation stops at minute " << CurrentTime << ".\n";
            stopped = true;
            break;
        }

        CurrentTime++;
    }

    // final simulation minute (a file with no requests ends at minute 1)
    int finalTime = CurrentTime - 1;
    if (finalTime < 1) finalTime = 1;
    if (stopped) finalTime = CurrentTime;

    int completedCount = 0;
    Ticket** completedTickets = completed.toArray(completedCount);

    int cancelledCount = 0;
    Ticket** cancelledTickets = cancelled.toArray(cancelledCount);

    Statistics stats(completedTickets, completedCount,
                     cancelledTickets, cancelledCount,
                     allRequests, requestCount,
                     technicians, technicianCount,
                     locations->size(), finalTime);

    OutputWriter writer(completedTickets, completedCount, &stats, outputFileName);

    if (interactive)
        std::cout << "\n";

    bool written = writer.WriteOutputFile();
    if (!written)
    {
        std::cout << "Output file could not be created: " << outputFileName << "\n";
        return;
    }

    if (interactive)
        stats.GenerateReport();

    std::cout << "Simulation ends, Output file created.\n";
}

// a waiting ticket can never be served if its technician type does not exist
bool Simulation::CannotBeServed()
{
    if (gtCount == 0 && !waitingNR.isEmpty()) return true;
    if (stCount == 0 && !waitingSR.isEmpty()) return true;
    if (stCount + gtCount == 0 && !waitingUR.isEmpty()) return true;
    return false;
}

void Simulation::CompleteServices()
{
    while (!inService.isEmpty() && inService.peek()->getFT() <= CurrentTime)
    {
        Ticket* t = inService.removeFirst();
        t->setStatus(TicketStatus::COMPLETED);
        completed.enqueue(t);

        for (int i = 0; i < technicianCount; i++)
        {
            Technician* tech = technicians[i];
            if (tech->getID() != t->getTID()) continue;

            tech->addBusyTime(t->getFT() - t->getST());
            tech->releaseTicket();

            if (tech->getType() == TechnicianType::GT)
                availableGT.returnGT(tech);
            else
                availableST.returnST(tech);
            break;
        }
    }
}

void Simulation::ReleaseRequests()
{
    // the input is sorted by QT, so every request that is due goes in now
    while (nextRequest < requestCount &&
           allRequests[nextRequest]->getQT() <= CurrentTime)
    {
        Ticket* t = allRequests[nextRequest];
        nextRequest++;
        t->setStatus(TicketStatus::WAITING);

        if (t->getType() == RequestType::NR)       waitingNR.enqueue(t);
        else if (t->getType() == RequestType::SR)  waitingSR.enqueue(t);
        else                                       waitingUR.insert(t);
    }
}

void Simulation::ProcessCancellation()
{
    while (nextCancel < cancellationCount &&
           allCancellations[nextCancel].CT <= CurrentTime)
    {
        cancelManager.CancelTicket(allCancellations[nextCancel].RID, CurrentTime);
        nextCancel++;
    }
}

void Simulation::Display()
{
    if (!interactive) return;

    std::cout << "\nMinute " << CurrentTime << "\n";

    // waiting tickets, each list in its own scheduling order
    std::cout << "Waiting UR (priority, QT, RID): ";
    waitingUR.printIDs();
    std::cout << "Waiting SR (FCFS): ";
    waitingSR.printIDs();
    std::cout << "Waiting NR (FCFS): ";
    waitingNR.printIDs();

    // available technicians by type
    std::cout << "Available technicians: ST=" << availableST.getCount()
              << " GT=" << availableGT.getCount() << "\n";

    // working technicians with the ticket each one is handling
    std::cout << "Working technicians:\n";
    bool anyWorking = false;
    for (int i = 0; i < technicianCount; i++)
    {
        Technician* tech = technicians[i];
        Ticket* t = tech->getCurrentTicket();
        if (t == nullptr) continue;

        anyWorking = true;
        std::cout << "  " << TechnicianTypeName(tech->getType()) << " " << tech->getID()
                  << " -> " << RequestTypeName(t->getType()) << " " << t->getRID()
                  << " at " << locations->getLocationName(t->getLID())
                  << ", PC " << t->getPC()
                  << " (" << configs->getCategory(t->getPC()) << ")"
                  << ", ST=" << t->getST()
                  << ", FT=" << t->getFT() << "\n";
    }
    if (!anyWorking) std::cout << "  -\n";

    // completed tickets, in FT then RID order
    std::cout << "Completed (FT, RID): ";
    completed.printIDs();

    // accepted cancellations
    std::cout << "Accepted cancellations: " << cancelled.getCount() << " -> ";
    cancelled.printIDs();

    std::cout << "Press Enter to advance to the next minute.";
    std::cin.get();
}

bool Simulation::Finished()
{
    return nextRequest >= requestCount &&
           nextCancel  >= cancellationCount &&
           waitingNR.isEmpty() && waitingSR.isEmpty() &&
           waitingUR.isEmpty() && inService.isEmpty();
}
