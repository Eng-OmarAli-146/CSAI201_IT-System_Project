#include "ProblemConfigurationQueue.h"
void ProblemConfigurationQueue::insertConfiguration(const ServiceConfiguration& c) { configurations.push_back(c); }
const ServiceConfiguration* ProblemConfigurationQueue::getConfigurationByPC(int pc) const {
    for (const auto& c : configurations)
        if (c.getPC() == pc) return &c;
    return nullptr;
}
int ProblemConfigurationQueue::getDuration(int pc) const {
    const auto* c = getConfigurationByPC(pc); return c ? c->getDuration() : 0;
}
std::string ProblemConfigurationQueue::getCategory(int pc) const {
    const auto* c = getConfigurationByPC(pc); return c ? c->getCategory() : "";
}
int ProblemConfigurationQueue::size() const { return static_cast<int>(configurations.size()); }

