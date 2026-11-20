#include "Simulation.h"
#include "Statistics.h"
#include "OutputWriter.h"
#include <iostream>

// "-" is shown when a list is empty
static std::string FormatIDs(const std::string& ids)
{
    return ids.empty() ? std::string("-") : ids;
}

// category (B / H) of the problem code, for the interactive display
static std::string FormatCategory(ProblemConfigurationQueue* configs, int pc)
{
    std::string category = configs->getCategory(pc);
    return category.empty() ? std::string("?") : category;
}

Simulation::Simulation(std::vector<Ticket*> requests,
                       std::vector<CancellationRequest> cancellations,
                       std::vector<Technician*> techs,
                       ProblemConfigurationQueue* configs,
                       int locationCount,
                       int mode)
    : CurrentTime(1), Mode(mode), configs(configs), locationCount(locationCount),
      allRequests(requests), allCancellations(cancellations), technicians(techs),
      nextRequest(0), nextCancel(0),
      scheduler(&waitingNR, &waitingSR, &waitingUR, &inService,
                &availableGT, &availableST, configs),
      cancelManager(&waitingNR, &inService, &availableGT, &availableST,
                    &technicians, &cancelled)
{
    // fill the available queues
    for (size_t i = 0; i < technicians.size(); i++)
    {
        if (technicians[i]->getType() == TechnicianType::GT)
            availableGT.insertGT(technicians[i]);
        else
            availableST.insertST(technicians[i]);
    }
}

void Simulation::Run()
{
    if (Mode != 1)
        std::cout << "Silent Mode, Simulation Starts...\n";

    while (!Finished())
    {
        CompleteServices();
        ReleaseRequests();
        ProcessCancellation();
        scheduler.AssignTickets(CurrentTime);
        Display();
        CurrentTime++;
    }

    // last minute that was actually processed (a zero-request run ends at minute 1)
    int finalTime = CurrentTime - 1;
    if (finalTime < 1) finalTime = 1;

    Statistics stats(&completed, &cancelled, &technicians, &allRequests,
                     locationCount, finalTime);

    OutputWriter writer(&completed, &stats);
    writer.WriteOutputFile();

    if (Mode == 1)
    {
        std::cout << "\n";
        stats.GenerateReport();
        stats.WriteLocationCounts(std::cout);
    }

    std::cout << "Simulation ends, Output file created.\n";
}

void Simulation::CompleteServices()
{
    while (!inService.isEmpty() && inService.peek()->getFT() <= CurrentTime)
    {
        Ticket* t = inService.removeFirst();
        t->setStatus(TicketStatus::COMPLETED);
        completed.push_back(t);

        for (size_t i = 0; i < technicians.size(); i++)
        {
            Technician* tech = technicians[i];
            if (tech->getID() == t->getTID())
            {
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
}

void Simulation::ReleaseRequests()
{
    // input is sorted by QT, so every request due at or before this minute goes in
    while (nextRequest < allRequests.size() &&
           allRequests[nextRequest]->getQT() <= CurrentTime)
    {
        Ticket* t = allRequests[nextRequest++];
        t->setStatus(TicketStatus::WAITING);

        if (t->getType() == RequestType::NR)       waitingNR.enqueue(t);
        else if (t->getType() == RequestType::SR)  waitingSR.enqueue(t);
        else                                       waitingUR.insert(t);
    }
}

void Simulation::ProcessCancellation()
{
    while (nextCancel < allCancellations.size() &&
           allCancellations[nextCancel].CT <= CurrentTime)
    {
        cancelManager.CancelTicket(allCancellations[nextCancel].RID, CurrentTime);
        nextCancel++;
    }
}

void Simulation::Display()
{
    if (Mode != 1) return;

    std::cout << "\nMinute " << CurrentTime << "\n";

    // waiting ticket IDs in the order they will be scheduled
    std::cout << "Waiting NR: " << FormatIDs(waitingNR.getIDs()) << "\n";
    std::cout << "Waiting SR: " << FormatIDs(waitingSR.getIDs()) << "\n";
    std::cout << "Waiting UR: " << FormatIDs(waitingUR.getIDs()) << "\n";

    // available technicians by type
    int availableGTCount = 0;
    int availableSTCount = 0;
    for (size_t i = 0; i < technicians.size(); i++)
    {
        if (!technicians[i]->isAvailable()) continue;
        if (technicians[i]->getType() == TechnicianType::GT) availableGTCount++;
        else                                                 availableSTCount++;
    }
    std::cout << "Available technicians: GT " << availableGTCount
              << ", ST " << availableSTCount << "\n";

    // working technicians with the ticket each one is handling
    std::cout << "Working technicians:";
    bool anyWorking = false;
    for (size_t i = 0; i < technicians.size(); i++)
    {
        Technician* tech = technicians[i];
        Ticket* t = tech->getCurrentTicket();
        if (!t) continue;

        anyWorking = true;
        std::cout << " T" << tech->getID() << "->RID " << t->getRID()
                  << " (LID " << t->getLID()
                  << ", category " << FormatCategory(configs, t->getPC()) << ")";
    }
    if (!anyWorking) std::cout << " -";
    std::cout << "\n";

    // cumulative completed ticket IDs
    std::cout << "Completed IDs:";
    if (completed.empty()) std::cout << " -";
    for (size_t i = 0; i < completed.size(); i++)
        std::cout << " " << completed[i]->getRID();
    std::cout << "\n";

    std::cout << "Press Enter to advance to the next minute.";
    std::cin.get();
}

bool Simulation::Finished()
{
    return nextRequest >= allRequests.size() &&
           nextCancel  >= allCancellations.size() &&
           waitingNR.isEmpty() && waitingSR.isEmpty() &&
           waitingUR.isEmpty() && inService.isEmpty();
}
