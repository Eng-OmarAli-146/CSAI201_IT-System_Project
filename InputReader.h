#include <iosfwd>
#include <string>
#include <utility>
#include <vector>
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
    std::vector<Ticket> requests;
    std::vector<std::pair<int, int>> cancellations; // {time, RID}
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
    const ProblemConfigurationQueue& getConfigurations() const;
    const TechnicianQueue& getTechnicians() const;
    std::vector<Ticket>& getRequests();
    const std::vector<Ticket>& getRequests() const;
    const std::vector<std::pair<int, int>>& getCancellations() const;
};
