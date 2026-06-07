#include "SmallBlind.h"
#include "../../mechanic/reward/RewardCommand.h"
#include "../card/Deck.h"
#include <iostream>

namespace system_p {

SmallBlind::SmallBlind(int ante)
{
  targetScore = 300 * ante;
}

std::string SmallBlind::getName() const
{
  return "Small Blind";
}

int SmallBlind::getTargetScore() const
{
  return targetScore;
}

bool SmallBlind::checkTarget(int score)
{
  std::cout << "[Small Blind] Checking score: " << score << " / " << targetScore << std::endl;
  return score >= targetScore;
}

std::unique_ptr<mechanic::PendingCommand>
SmallBlind::createSkipRewardCommand(int& remainingPlays, Deck& /*deck*/, int& /*freeRerolls*/) const
{
  // Skip Small Blind -> +1 hand di blind berikutnya
  return std::make_unique<mechanic::PendingCommand>(
    std::make_unique<mechanic::BonusHandCommand>(remainingPlays),
    mechanic::CommandTiming::NextBlind);
}

} // namespace system_p