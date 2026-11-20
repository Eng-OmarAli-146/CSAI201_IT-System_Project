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
| Containers | `WaitingNRQueue`, `WaitingSRQueue`, `WaitingURPriorityQueue`, `InServiceList`, `AvailableGTQueue`, `AvailableSTQueue`, `TechnicianQueue`, `ProblemConfigurationQueue`, `LocationManager` |
| Engine | `Scheduler`, `CancellationManager`, `Simulation` |
| I/O | `InputReader`, `OutputWriter`, `Statistics` |
| Entry point | `main.cpp` |

## Build

Plain C++ — just a g++ compiler, no CMake and no extra tools:

```bash
g++ -std=c++17 *.cpp -o it_system
```

Or with the included Makefile (which runs exactly the same command):

```bash
make          # build
make run      # build + run
make clean    # remove the executable
```

## Run

```bash
./it_system          # start from the directory that contains input.txt
```

Choose `1` for the step-by-step interactive trace or `2` for silent mode. In
silent mode only the final report is printed. Results are written to
`output.txt` in the current directory.

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
```

followed by the report:

```
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
```

Averages and percentages are printed to two decimal places. The same file is
produced in both modes.
