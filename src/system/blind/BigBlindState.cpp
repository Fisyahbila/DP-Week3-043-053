#include "BigBlindState.h"
#include "BossBlindState.h"
#include "../../mechanic/reward/RewardCommand.h"
#include "../card/Deck.h"
#include <iostream>

namespace system_p {

std::string BigBlindState::getName() const {
    return "Big Blind";
}

int BigBlindState::getTargetScore(int ante) const {
    return 800 * ante;
}

int BigBlindState::getRewardMoney() const {
    return 4;
}

std::unique_ptr<mechanic::PendingCommand> BigBlindState::createSkipRewardCommand(int& /*remainingPlays*/, Deck& deck, int& /*freeRerolls*/) const {
    return std::make_unique<mechanic::PendingCommand>(
        std::make_unique<mechanic::FreePlayingCardCommand>(deck),
        mechanic::CommandTiming::Start);
}

std::shared_ptr<BlindState> BigBlindState::extState(int& /*ante*/) {
    return std::make_shared<BossBlindState>();
}

} // namespace system_p
