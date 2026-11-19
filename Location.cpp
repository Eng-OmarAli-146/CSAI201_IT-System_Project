#include "Location.h"
Location::Location(int id, const std::string& name) : lid(id), name(name) {}
int Location::getID() const { return lid; }
const std::string& Location::getName() const { return name; }
