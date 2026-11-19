#pragma once
#include <iosfwd>
#include <string>
#include <utility>
#include <vector>
#include "Definitions.h"
#include "CancellationManager.h"   // CancellationRequest
#include "LocationManager.h"
#include "ProblemConfigurationQueue.h"
#include "TechnicianQueue.h"
#include "Ticket.h"
class InputReader {
private:
    std::string fileName;
    LocationManager locations;
    ProblemConfigurationQueue configurations;
    TechnicianQueue technicians;
    std::vector<Ticket> allRequests;
    std::vector<std::pair<int, int>> allCancellations; // {time, RID}
    static RequestType parseRequestType(const std::string& value);
    static TechnicianType parseTechnicianType(const std::string& value);
public:
    explicit InputReader(const std::string& fileName = "input.txt");
    bool LoadFile();
    bool LoadLocations(std::istream& input);
    bool LoadConfigurations(std::istream& input);
    bool LoadTechnicians(std::istream& input);
    bool LoadRequests(std::istream& input);
    bool LoadCancellations(std::istream& input);
    const LocationManager& getLocations() const;
    ProblemConfigurationQueue* getConfigurations();
    std::vector<Technician*> getTechnicians();
    std::vector<Ticket*> getAllRequests();
    std::vector<CancellationRequest> getAllCancellations();
};
