#include "Simulation.h"
#include "Statistics.h"
#include "OutputWriter.h"
#include <iostream>

Simulation::Simulation(std::vector<Ticket*> requests,
                       std::vector<CancellationRequest> cancellations,
                       std::vector<Technician*> techs,
                       ProblemConfigurationQueue* configs,
                       int mode)
    : CurrentTime(1), Mode(mode),
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
    while (!Finished())
    {
        CompleteServices();
        ReleaseRequests();
        ProcessCancellation();
        scheduler.AssignTickets(CurrentTime);
        Display();
        CurrentTime++;
    }

    Statistics stats(&completed, &cancelled, &technicians, CurrentTime - 1);
    stats.GenerateReport();

    OutputWriter writer(&completed, &stats);
    writer.WriteOutputFile();
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
    while (nextRequest < allRequests.size() &&
           allRequests[nextRequest]->getQT() == CurrentTime)
    {
        Ticket* t = allRequests[nextRequest++];
        t->setStatus(TicketStatus::WAITING);

        if (t->getType() == RequestType::NR)       waitingNR.enqueue(t);
        else if (t->getType() == RequestType::SR)  waitingSR.enqueue(t);
        else                          waitingUR.insert(t);
    }
}

void Simulation::ProcessCancellation()
{
    while (nextCancel < allCancellations.size() &&
           allCancellations[nextCancel].CT == CurrentTime)
    {
        cancelManager.CancelTicket(allCancellations[nextCancel].RID);
        nextCancel++;
    }
}

void Simulation::Display()
{
    if (Mode != 1) return;

    std::cout << "\nCurrent Time: " << CurrentTime << "\n";
    std::cout << "Waiting NR: ";  waitingNR.print();
    std::cout << "Waiting SR: ";  waitingSR.print();
    std::cout << "Waiting UR: ";  waitingUR.print();
    std::cout << "In Service: ";  inService.print();
    std::cout << "Completed: " << completed.size() << "\n";
    std::cout << "Press Enter...";
    std::cin.get();
}

bool Simulation::Finished()
{
    return nextRequest >= allRequests.size() &&
           nextCancel  >= allCancellations.size() &&
           waitingNR.isEmpty() && waitingSR.isEmpty() &&
           waitingUR.isEmpty() && inService.isEmpty();
}
