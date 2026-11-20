#pragma once
#include <iostream>
#include <string>
#include "Definitions.h"
#include "LocationManager.h"
#include "ProblemConfigurationQueue.h"
#include "TechnicianQueue.h"
#include "Ticket.h"
#include "TicketQueue.h"
#include "CancellationQueue.h"

// Reads the input file and keeps every record in the structure that suits it.
class InputReader
{
private:
    std::string fileName;
    LocationManager           locations;
    ProblemConfigurationQueue configurations;
    TechnicianQueue           technicians;
    TicketQueue               allRequests;
    CancellationQueue         allCancellations;

    static RequestType parseRequestType(const std::string& value);

public:
    explicit InputReader(const std::string& fileName);

    bool LoadFile();
    bool LoadLocations(std::istream& input);
    bool LoadConfigurations(std::istream& input);
    bool LoadTechnicians(std::istream& input);
    bool LoadRequests(std::istream& input);
    bool LoadCancellations(std::istream& input);

    const LocationManager&     getLocations() const;
    ProblemConfigurationQueue* getConfigurations();
    Technician**               getTechnicians(int& count);
    TicketQueue&               getAllRequests();
    CancellationQueue&         getAllCancellations();
};
