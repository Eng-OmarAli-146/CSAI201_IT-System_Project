#include <iostream>
#include <string>
#include "InputReader.h"
#include "Simulation.h"

int main()
{
    // 1) interactive or silent
    std::cout << "Choose mode [I=Interactive, S=Silent]: ";
    std::string modeLine;
    std::getline(std::cin, modeLine);

    bool interactive = false;
    if (!modeLine.empty() && (modeLine[0] == 'I' || modeLine[0] == 'i'))
        interactive = true;

    // 2) input file name
    std::cout << "Enter input file name [input.txt]: ";
    std::string inputName;
    std::getline(std::cin, inputName);
    if (inputName.empty()) inputName = "input.txt";

    // 3) output file name
    std::cout << "Enter output file name [output.txt]: ";
    std::string outputName;
    std::getline(std::cin, outputName);
    if (outputName.empty()) outputName = "output.txt";

    InputReader reader(inputName);
    if (!reader.LoadFile())
        return 1;

    // the simulation works on plain arrays copied from the loaded lists
    int requestCount = 0;
    Ticket** requests = reader.getAllRequests().toArray(requestCount);

    int cancellationCount = 0;
    CancellationRequest* cancellations = reader.getAllCancellations().toArray(cancellationCount);

    int technicianCount = 0;
    Technician** technicians = reader.getTechnicians(technicianCount);

    Simulation sim(requests, requestCount,
                   cancellations, cancellationCount,
                   technicians, technicianCount,
                   reader.getConfigurations(),
                   &reader.getLocations(),
                   interactive,
                   outputName);
    sim.Run();

    return 0;
}
