#ifndef BLIND_MANAGER_H
#define BLIND_MANAGER_H

#include "BlindRule.h"
#include <memory>
#include <string>

namespace system_p {

class BlindManager {
public:
    BlindManager();
    ~BlindManager();

    void selectBlind(int ante, int blindTypeIndex);
    
    BlindRule* getCurrentBlind() const;
    bool isTargetMet(int score) const;
    int getCurrentTargetScore() const;
    std::string getCurrentBlindName() const;

private:
    std::unique_ptr<BlindRule> currentBlind;
};

} // namespace system_p

#endif // BLIND_MANAGER_H
