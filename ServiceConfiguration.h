#pragma once
#include <string>
class ServiceConfiguration {
private:
    int pc{};
    std::string category;
    int duration{};
public:
    ServiceConfiguration() = default;
    ServiceConfiguration(int pc, const std::string& category, int duration);
    int getPC() const;
    const std::string& getCategory() const;
    int getDuration() const;
};
