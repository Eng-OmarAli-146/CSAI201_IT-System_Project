#include "TechnicianQueue.h"
#include <iostream>
void TechnicianQueue::insertTechnician(const Technician& t) { technicians.push_back(t); }
Technician* TechnicianQueue::getTechnicianByID(int id) {
    for (auto& t : technicians) if (t.getID() == id) return &t;
    return nullptr;
}
const Technician* TechnicianQueue::getTechnicianByID(int id) const {
    for (const auto& t : technicians) if (t.getID() == id) return &t;
    return nullptr;
}
std::vector<Technician*> TechnicianQueue::getAllTechnicians() {
    std::vector<Technician*> result;
    result.reserve(technicians.size());
    for (auto& t : technicians) result.push_back(&t);
    return result;
}
bool TechnicianQueue::updateTechnician(int id, const Technician& t) {
    for (auto& current : technicians) {
        if (current.getID() == id) { current = t; return true; }
    }
    return false;
}
void TechnicianQueue::printWorkingTechnicians() const {
    for (const auto& t : technicians)
        if (!t.isAvailable()) std::cout << "Technician " << t.getID() << " is working\n";
}
int TechnicianQueue::size() const { return static_cast<int>(technicians.size()); }

