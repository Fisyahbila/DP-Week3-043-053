#include "BigBlind.h"
#include "../../mechanic/reward/RewardCommand.h"
#include "../card/Deck.h"
#include <iostream>

namespace system_p {

BigBlind::BigBlind(int ante)
{
  targetScore = 800 * ante;
}

std::string BigBlind::getName() const
{
  return "Big Blind";
}

int BigBlind::getTargetScore() const
{
  return targetScore;
}

bool BigBlind::checkTarget(int score)
{
  std::cout << "[Big Blind] Checking score: " << score << " / " << targetScore << std::endl;
  return score >= targetScore;
}

std::unique_ptr<mechanic::PendingCommand>
BigBlind::createSkipRewardCommand(int& /*remainingPlays*/, Deck& deck, int& /*freeRerolls*/) const
{
  // Skip Big Blind -> tambah kartu acak ke deck saat Start
  return std::make_unique<mechanic::PendingCommand>(
    std::make_unique<mechanic::FreePlayingCardCommand>(deck),
    mechanic::CommandTiming::Start);
}

} // namespace system_p