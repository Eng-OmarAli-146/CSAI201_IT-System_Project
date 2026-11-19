#include "LocationManager.h"
void LocationManager::addLocation(const Location& location) { locations.push_back(location); }
const Location* LocationManager::getLocation(int id) const {
    for (const auto& location : locations)
        if (location.getID() == id) return &location;
    return nullptr;
}
std::string LocationManager::getLocationName(int id) const {
    const Location* location = getLocation(id);
    return location ? location->getName() : "";
}
int LocationManager::size() const { return static_cast<int>(locations.size()); }
