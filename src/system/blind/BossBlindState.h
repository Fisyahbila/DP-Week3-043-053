#ifndef BOSS_BLIND_STATE_H
#define BOSS_BLIND_STATE_H

#include "BlindState.h"

namespace system_p {

class BossBlindState : public BlindState {
public:
    std::string getName() const override;
    int getTargetScore(int ante) const override;
    int getRewardMoney() const override;
    std::unique_ptr<mechanic::PendingCommand> createSkipRewardCommand(int& remainingPlays, Deck& deck, int& freeRerolls) const override;
    std::shared_ptr<BlindState> extState(int& ante) override;
};

} // namespace system_p

#endif // BOSS_BLIND_STATE_H
