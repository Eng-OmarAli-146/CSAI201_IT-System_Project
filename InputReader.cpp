#include "InputReader.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
InputReader::InputReader(const std::string& fileName) : fileName(fileName) {}
RequestType InputReader::parseRequestType(const std::string& value) {
    if (value == "SR" || value == "sr" || value == "1") return RequestType::SR;
    if (value == "UR" || value == "ur" || value == "2") return RequestType::UR;
    return RequestType::NR;
}
TechnicianType InputReader::parseTechnicianType(const std::string& value) {
    if (value == "ST" || value == "st" || value == "1") return TechnicianType::ST;
    return TechnicianType::GT;
}
bool InputReader::LoadFile() {
    std::ifstream input(fileName);
    if (!input.is_open()) {
        std::cerr << "Cannot open input file: " << fileName << '\n';
        return false;
    }
    try {
        return LoadLocations(input) &&
               LoadConfigurations(input) &&
               LoadTechnicians(input) &&
               LoadRequests(input) &&
               LoadCancellations(input);
    } catch (const std::exception& error) {
        std::cerr << "Input error: " << error.what() << '\n';
        return false;
    }
}
bool InputReader::LoadLocations(std::istream& input) {
    int count;
    if (!(input >> count) || count < 0) return false;
    for (int i = 0; i < count; ++i) {
        int id;
        std::string name;
        if (!(input >> id >> name)) return false;
        locations.addLocation(Location(id, name));
    }
    return true;
}
bool InputReader::LoadConfigurations(std::istream& input) {
    int count;
    if (!(input >> count) || count < 0) return false;
    for (int i = 0; i < count; ++i) {
        int pc, duration;
        std::string category;
        if (!(input >> pc >> category >> duration)) return false;
        configurations.insertConfiguration(ServiceConfiguration(pc, category, duration));
    }
    return true;
}
bool InputReader::LoadTechnicians(std::istream& input) {
    int count;
    if (!(input >> count) || count < 0) return false;
    for (int i = 0; i < count; ++i) {
        int id;
        std::string type;
        if (!(input >> id >> type)) return false;
        technicians.insertTechnician(Technician(id, parseTechnicianType(type)));
    }
    return true;
}
bool InputReader::LoadRequests(std::istream& input) {
    int count;
    if (!(input >> count) || count < 0) return false;
    for (int i = 0; i < count; ++i) {
        int rid, qt, lid, pc, pr;
        std::string type;
        if (!(input >> rid >> qt >> lid >> pc >> pr >> type)) return false;
        allRequests.emplace_back(rid, qt, lid, pc, pr, parseRequestType(type));
    }
    return true;
}
bool InputReader::LoadCancellations(std::istream& input) {
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i) {
        int time, rid;
        if (!(input >> time >> rid)) return false;
        allCancellations.emplace_back(time, rid);
    }
    return true;
}
const LocationManager& InputReader::getLocations() const { return locations; }
ProblemConfigurationQueue* InputReader::getConfigurations() { return &configurations; }
std::vector<Technician*> InputReader::getTechnicians() { return technicians.getAllTechnicians(); }
std::vector<Ticket*> InputReader::getAllRequests() {
    // the tickets are stored by value inside allRequests, which is fully loaded
    // at this point, so pointers to its elements stay valid during the simulation
    std::vector<Ticket*> result;
    result.reserve(allRequests.size());
    for (auto& ticket : allRequests) result.push_back(&ticket);
    return result;
}
std::vector<CancellationRequest> InputReader::getAllCancellations() {
    std::vector<CancellationRequest> result;
    result.reserve(allCancellations.size());
    for (const auto& cancellation : allCancellations) {
        CancellationRequest request;
        request.CT  = cancellation.first;
        request.RID = cancellation.second;
        result.push_back(request);
    }
    return result;
}

