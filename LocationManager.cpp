#include <vector>
#include "Location.h"
class LocationManager {
private:
    std::vector<Location> locations;
public:
    void addLocation(const Location& location);
    const Location* getLocation(int id) const;
    std::string getLocationName(int id) const;
    int size() const;
};
