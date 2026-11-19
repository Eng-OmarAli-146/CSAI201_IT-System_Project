#include <vector>
#include "Technician.h"
class TechnicianQueue {
private:
    std::vector<Technician> technicians;
public:
    void insertTechnician(const Technician& technician);
    Technician* getTechnicianByID(int id);
    const Technician* getTechnicianByID(int id) const;
    bool updateTechnician(int id, const Technician& technician);
    void printWorkingTechnicians() const;
    int size() const;
};

