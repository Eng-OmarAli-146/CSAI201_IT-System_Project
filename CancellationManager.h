class CancellationManager
{
public:

    bool CancelTicket(int RID);

    bool CancelWaitingNR(int RID);

    bool CancelAssignedNR(int RID);
};
