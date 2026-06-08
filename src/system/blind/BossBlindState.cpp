#include "BossBlindState.h"
#include "SmallBlindState.h"
#include "../../mechanic/reward/RewardCommand.h"
#include "../card/Deck.h"
#include <iostream>

namespace system_p {

std::string BossBlindState::getName() const {
    return "Boss Blind";
}

int BossBlindState::getTargetScore(int ante) const {
    return 600 * ante;
}

int BossBlindState::getRewardMoney() const {
    return 5;
}

std::unique_ptr<mechanic::PendingCommand> BossBlindState::createSkipRewardCommand(int& /*remainingPlays*/, Deck& /*deck*/, int& freeRerolls) const {
    return std::make_unique<mechanic::PendingCommand>(
        std::make_unique<mechanic::FreeRerollCommand>(freeRerolls),
        mechanic::CommandTiming::NextShop);
}

std::shared_ptr<BlindState> BossBlindState::extState(int& ante) {
    ante++;
    return std::make_shared<SmallBlindState>();
}

} // namespace system_p
