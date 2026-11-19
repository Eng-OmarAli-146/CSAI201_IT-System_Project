#pragma once
#include "Definitions.h"
#include "Ticket.h"
class Technician {
private:
    int id{};
    TechnicianType type{TechnicianType::GT};
    int busyTime{};
    bool available{true};
    Ticket* currentTicket{nullptr};
public:
    Technician() = default;
    Technician(int id, TechnicianType type);
    int getID() const; TechnicianType getType() const;
    int getBusyTime() const; bool isAvailable() const;
    Ticket* getCurrentTicket() const;
    void assignTicket(Ticket* ticket); void releaseTicket(); void addBusyTime(int amount);
};
