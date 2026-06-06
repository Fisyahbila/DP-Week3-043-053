#pragma once
#include "../card/Deck.h"
#include "../card/HandState.h"
#include "../scoring/ScoringRule.h"
#include "../blind/BlindManager.h"
#include "RoundState.h"
#include "../../mechanic/reward/RewardRule.h"
#include "../../mechanic/reward/RewardManager.h"

namespace system_p {

class GameManager {
public:
  GameManager();
  void runSession();

private:
  bool playBlind(int ante, int blindIndex);
  void printHand();

  Deck deck;
  HandState handState;
  ScoringRule scoringRule;
  BlindManager blindManager;
  RoundState roundState;

  mechanic::RewardManager rewardManager; // totalMoney sekarang ada di sini
  bool isGameOver;
};

} // namespace system_p
