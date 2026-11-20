#include "InputReader.h"
#include <fstream>

InputReader::InputReader(const std::string& fileName) : fileName(fileName) {}

RequestType InputReader::parseRequestType(const std::string& value)
{
    if (value == "SR" || value == "sr") return RequestType::SR;
    if (value == "UR" || value == "ur") return RequestType::UR;
    return RequestType::NR;
}

bool InputReader::LoadFile()
{
    std::ifstream input(fileName.c_str());
    if (!input.is_open())
    {
        std::cout << "Cannot open input file: " << fileName << "\n";
        return false;
    }

    return LoadLocations(input) &&
           LoadConfigurations(input) &&
           LoadTechnicians(input) &&
           LoadRequests(input) &&
           LoadCancellations(input);
}

// L, then L location tokens. The location id is the row number.
bool InputReader::LoadLocations(std::istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        std::string name;
        if (!(input >> name)) return false;
        locations.addLocation(Location(i + 1, name));
    }
    return true;
}

// K, then K rows "category duration". The problem code is the row number.
bool InputReader::LoadConfigurations(std::istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        int duration;
        std::string category;
        if (!(input >> category >> duration)) return false;
        configurations.insertConfiguration(ServiceConfiguration(i + 1, category, duration));
    }
    return true;
}

// one line with the two counts: ST_count GT_count
bool InputReader::LoadTechnicians(std::istream& input)
{
    int stCount;
    int gtCount;
    if (!(input >> stCount >> gtCount) || stCount < 0 || gtCount < 0) return false;

    // ids increase, all ST technicians first and then all GT technicians
    int id = 1;
    for (int i = 0; i < stCount; ++i)
        technicians.insertTechnician(Technician(id++, TechnicianType::ST));

    for (int i = 0; i < gtCount; ++i)
        technicians.insertTechnician(Technician(id++, TechnicianType::GT));

    return true;
}

// R, then R rows: TYPE QT RID LID PC (and PR only for UR)
bool InputReader::LoadRequests(std::istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        std::string type;
        if (!(input >> type)) return false;

        RequestType requestType = parseRequestType(type);

        int qt;
        int rid;
        int lid;
        int pc;
        if (!(input >> qt >> rid >> lid >> pc)) return false;

        int pr = 0;                       // only UR tickets have a priority
        if (requestType == RequestType::UR && !(input >> pr)) return false;

        allRequests.enqueue(new Ticket(rid, qt, lid, pc, pr, requestType));
    }
    return true;
}

// C, then C rows: CT RID
bool InputReader::LoadCancellations(std::istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        CancellationRequest request;
        if (!(input >> request.CT >> request.RID)) return false;
        allCancellations.enqueue(request);
    }
    return true;
}

const LocationManager& InputReader::getLocations() const { return locations; }

ProblemConfigurationQueue* InputReader::getConfigurations() { return &configurations; }

Technician** InputReader::getTechnicians(int& count)
{
    return technicians.toArray(count);
}

TicketQueue& InputReader::getAllRequests() { return allRequests; }

CancellationQueue& InputReader::getAllCancellations() { return allCancellations; }
