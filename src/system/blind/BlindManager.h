#ifndef BLIND_MANAGER_H
#define BLIND_MANAGER_H

#include "BlindState.h"
#include <memory>
#include <string>

namespace system_p {

class BlindManager {
public:
    BlindManager();
    ~BlindManager();

    void selectBlind(int ante, int blindTypeIndex);
    
    BlindState* getCurrentBlind() const;
    bool isTargetMet(int score) const;
    int getCurrentTargetScore() const;
    std::string getCurrentBlindName() const;

    std::shared_ptr<BlindState> getCurrentBlindState() const { return currentBlindState; }
    void setCurrentBlindState(std::shared_ptr<BlindState> state) { currentBlindState = state; }
    int getCurrentAnte() const { return currentAnte; }
    void setCurrentAnte(int ante) { currentAnte = ante; }

private:
    std::shared_ptr<BlindState> currentBlindState;
    int currentAnte;
};

} // namespace system_p

#endif // BLIND_MANAGER_H
