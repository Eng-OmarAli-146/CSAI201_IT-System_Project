#include "LocationManager.h"

LocationManager::LocationManager() : items(nullptr), capacity(0), count(0) {}

void LocationManager::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Location** bigger = new Location*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void LocationManager::addLocation(const Location& location)
{
    if (count == capacity) grow();

    items[count] = new Location(location.getID(), location.getName());
    count++;
}

const Location* LocationManager::getLocation(int id) const
{
    if (id < 1 || id > count) return nullptr;
    return items[id - 1];
}

std::string LocationManager::getLocationName(int id) const
{
    const Location* location = getLocation(id);
    if (location == nullptr) return std::string("");
    return location->getName();
}

int LocationManager::size() const { return count; }
