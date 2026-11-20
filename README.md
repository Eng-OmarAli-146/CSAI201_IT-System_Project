Just begging

# IT System — Service Center Simulation (CSAI201)

A discrete-time simulation of an IT service center. Requests (tickets) arrive at a
queue time and wait for a technician; general technicians (GT) serve normal
requests (NR), specialists (ST) serve scheduled requests (SR), and urgent
requests (UR) are served by priority by either type.

## Structure

| Layer | Files |
|---|---|
| Enumerations / shared types | `Definitions.h` |
| Domain entities | `Ticket`, `Technician`, `Location`, `ServiceConfiguration`, `CancellationRequest` |
| Containers (all hand-written) | `TicketQueue`, `CancellationQueue`, `WaitingNRQueue`, `WaitingSRQueue`, `WaitingURPriorityQueue`, `InServiceList`, `AvailableGTQueue`, `AvailableSTQueue`, `TechnicianQueue`, `ProblemConfigurationQueue`, `LocationManager` |
| Engine | `Scheduler`, `CancellationManager`, `Simulation` |
| I/O | `InputReader`, `OutputWriter`, `Statistics` |
| Entry point | `main.cpp` |

## Build

Plain C++ — just a g++ compiler, no CMake and no extra tools:

```bash
g++ -std=c++11 -Wall -Wextra *.cpp -o it_system
```

Or with the included Makefile (which runs exactly the same command):

```bash
make          # build
make run      # build + run
make clean    # remove the executable
```

## Run

```bash
./it_system
```

The program then asks for three things (press Enter to accept the default):

```
Choose mode [I=Interactive, S=Silent]: I
Enter input file name [input.txt]: input.txt
Enter output file name [output.txt]: output.txt
```

Interactive mode prints the state of the IT unit at every minute and waits for
Enter; silent mode prints only `Silent Mode`, `Simulation Starts...` and
`Simulation ends, Output file created.` Both modes write exactly the same
output file.

No STL container is used: every queue is a hand-written linked list and every
heap is a hand-written array based binary heap.

## Input format (`input.txt`)

```
<L>                          number of university locations
<name> ...                   L location codes/names (one token each; LID = row number)
<K>                          number of problem configurations
<category> <duration>        K rows; category is B or H (PC = row number, starting at 1)
<ST_count> <GT_count>        technicians of the centralized IT unit
<R>                          number of requests
<TYPE> <QT> <RID> <LID> <PC> [<PR>]
<C>                          number of cancellations
<CT> <RID>
```

* `TYPE` is `NR`, `SR` or `UR`; only `UR` records carry the extra priority `PR`.
* Technician IDs are assigned automatically: all ST technicians first, then all GT.
* `QT` = request time, `CT` = cancellation time; records are sorted by time and keep
  file order for equal times.
* NR/UR must refer to a category `B` problem code, SR to category `H`.
* Only NR tickets can be cancelled; SR, UR, completed and unknown IDs are ignored.

## Output format (`output.txt`)

A table of completed tickets sorted by ascending `FT`, then `RID`:

```
FT RID QT WT ST AT TID LID
4 1 1 0 1 1 3 1
4 3 1 0 1 1 2 3
6 2 1 0 1 1 1 2
Requests: 4 [NR: 2, SR: 1, UR: 1]
Completed: 3 [NR: 1, SR: 1, UR: 1]
Cancelled: 1
Locations: 3
Technicians: 3 [Specialist: 1, General: 2]
Average waiting time: 0.00
Average resolution time: 3.67
Average busy time: 3.67
Simulation time: 6
Average utilisation: 61.11%
Individual busy times: technician 1 = 5; technician 2 = 3; technician 3 = 3. Total = 11 minutes.

Tickets by location:
Location 1: 1
Location 2: 2
Location 3: 1
```

Averages and percentages are printed with two decimal places. `WT = ST - QT`
and resolution time = `FT - QT`; cancelled tickets are excluded from both.
Averages are `0.00` when nothing completed, and utilisation is `0.00` when
there are no technicians.
