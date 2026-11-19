#include <iostream>
#include "InputReader.h"
#include "Simulation.h"

int main()
{
    InputReader reader;
    reader.LoadFile();

    int mode;
    std::cout << "1) Interactive  2) Silent : ";
    std::cin >> mode;
    std::cin.ignore(1000, '\n');

    Simulation sim(reader.getAllRequests(),
                   reader.getAllCancellations(),
                   reader.getTechnicians(),
                   reader.getConfigurations(),
                   mode);
    sim.Run();

    return 0;
}
