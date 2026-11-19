cmake_minimum_required(VERSION 3.10)
project(ITSystemProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(it_system
    main.cpp
    InputReader.cpp
    Location.cpp
    LocationManager.cpp
    ServiceConfiguration.cpp
    ProblemConfigurationQueue.cpp
    Technician.cpp
    TechnicianQueue.cpp
    Ticket.cpp
    Statistics.cpp
    OutputWriter.cpp
    Simulation.cpp
    Scheduler.cpp
    CancellationManager.cpp
    AvailableGTQueue.cpp
    AvailableSTQueue.cpp
    InServiceList.cpp
    WaitingNRQueue.cpp
    WaitingSRQueue.cpp
    WaitingURPriorityQueue.cpp
)

# keep the default input file next to the executable
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt
               COPYONLY)
