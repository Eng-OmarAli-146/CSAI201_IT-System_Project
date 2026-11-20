#pragma once
#include <string>
#include "Location.h"

// Locations are stored in a dynamic array indexed by the location ID:
// the location with id 1 is at index 0, id 2 at index 1, and so on.
class LocationManager
{
private:
    Location** items;
    int capacity;
    int count;

    void grow();   // doubles the array when it is full

public:
    LocationManager();

    void addLocation(const Location& location);
    const Location* getLocation(int id) const;
    std::string getLocationName(int id) const;
    int size() const;
};
