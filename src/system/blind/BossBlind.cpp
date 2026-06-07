#include "BossBlind.h"
#include "../../mechanic/reward/RewardCommand.h"
#include "../card/Deck.h"
#include <iostream>

namespace system_p {

BossBlind::BossBlind(int ante)
{
  targetScore = 1600 * ante;
}

std::string BossBlind::getName() const
{
  return "Boss Blind";
}

int BossBlind::getTargetScore() const
{
  return targetScore;
}

bool BossBlind::checkTarget(int score)
{
  std::cout << "[Boss Blind] Checking score: " << score << " / " << targetScore << std::endl;
  std::cout << "[Boss Blind] Active Modifier: None (Standard Boss)" << std::endl;
  return score >= targetScore;
}

std::unique_ptr<mechanic::PendingCommand> BossBlind::createSkipRewardCommand(int& /*remainingPlays*/,
                                                                             Deck& /*deck*/,
                                                                             int& freeRerolls) const
{
  // Skip Boss Blind -> +1 free reroll di toko berikutnya
  return std::make_unique<mechanic::PendingCommand>(
    std::make_unique<mechanic::FreeRerollCommand>(freeRerolls),
    mechanic::CommandTiming::NextShop);
}

} // namespace system_p