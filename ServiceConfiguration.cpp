#include "ServiceConfiguration.h"
ServiceConfiguration::ServiceConfiguration(int pc, const std::string& category, int duration)
    : pc(pc), category(category), duration(duration) {}
int ServiceConfiguration::getPC() const { return pc; }
const std::string& ServiceConfiguration::getCategory() const { return category; }
int ServiceConfiguration::getDuration() const { return duration; }
