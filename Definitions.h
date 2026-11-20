#pragma once

enum class RequestType {
    NR,
    SR,
    UR
};
enum class TechnicianType {
    GT,
    ST
};
enum class TicketStatus {
    NEW,
    WAITING,
    IN_SERVICE,
    COMPLETED,
    CANCELLED
};

// one cancellation record read from the input file (CT = cancellation time)
struct CancellationRequest
{
    int CT;
    int RID;
};
