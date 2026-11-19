#pragma once
#include <string>
#include <vector>
#include "ServiceConfiguration.h"
class ProblemConfigurationQueue {
private:
    std::vector<ServiceConfiguration> configurations;
public:
    void insertConfiguration(const ServiceConfiguration& configuration);
    const ServiceConfiguration* getConfigurationByPC(int pc) const;
    int getDuration(int pc) const;
    std::string getCategory(int pc) const;
    int size() const;
};
