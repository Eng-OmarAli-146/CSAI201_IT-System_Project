#include "Definitions.h"
class Ticket {
private:
    int rid{}, qt{}, lid{}, pc{}, pr{};
    int at{-1}, st{-1}, ft{-1}, tid{-1};
    RequestType type{RequestType::NR};
    TicketStatus status{TicketStatus::NEW};
public:
    Ticket() = default;
    Ticket(int rid, int qt, int lid, int pc, int pr, RequestType type);
    int getRID() const; int getQT() const; int getLID() const;
    int getPC() const; int getPR() const;
    int getAT() const; int getST() const; int getFT() const; int getTID() const;
    RequestType getType() const; TicketStatus getStatus() const;
    void setAT(int value); void setST(int value); void setFT(int value);
    void setTID(int value); void setType(RequestType value); void setStatus(TicketStatus value);
};
