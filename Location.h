#include <string>
class Location {
private:
    int lid{};
    std::string name;
public:
    Location() = default;
    Location(int id, const std::string& name);
    int getID() const;
    const std::string& getName() const;
};

