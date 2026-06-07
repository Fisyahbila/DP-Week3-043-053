#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "../../mechanic/reward/RewardCommand.h"
#include "../card/Deck.h"
#include <iostream>

namespace system_p {

std::string SmallBlindState::getName() const {
    return "Small Blind";
}

int SmallBlindState::getTargetScore(int ante) const {
    return 300 * ante;
}

int SmallBlindState::getRewardMoney() const {
    return 3;
}

std::unique_ptr<mechanic::PendingCommand> SmallBlindState::createSkipRewardCommand(int& remainingPlays, Deck& /*deck*/, int& /*freeRerolls*/) const {
    return std::make_unique<mechanic::PendingCommand>(
        std::make_unique<mechanic::BonusHandCommand>(remainingPlays),
        mechanic::CommandTiming::NextBlind);
}

std::shared_ptr<BlindState> SmallBlindState::extState(int& /*ante*/) {
    return std::make_shared<BigBlindState>();
}

} // namespace system_p
