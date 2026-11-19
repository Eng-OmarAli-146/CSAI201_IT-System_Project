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

With CMake:

```bash
cmake -S . -B build
cmake --build build
```

or with plain make:

```bash
make
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
<number of locations>
<LID> <name>
...
<number of problem configurations>
<PC> <category> <duration>
...
<number of technicians>
<TID> GT|ST
...
<number of requests>
<RID> <QT> <LID> <PC> <PR> NR|SR|UR
...
<number of cancellations>
<CT> <RID>
```

* `QT` queue (arrival) time, `PR` priority (higher is more urgent), `CT`
  cancellation time.
* Requests are released in the order they appear, so they must be listed in
  non-decreasing `QT` order.
* Every `PC` used by a request should exist in the configuration section, and a
  GT technician must be available for NR requests so that no queue is starved.

## Output format (`output.txt`)

```
FT RID QT WT ST AT TID LID
```

followed by a summary block (completed/cancelled counts, average waiting time,
average response time, total busy time and technician utilization).
