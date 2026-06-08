#pragma once
#include "RoundState.h"
#include "../card/Deck.h"
#include "../card/HandState.h"
#include "../scoring/ScoringRule.h"
#include "../blind/BlindManager.h"
#include "../../mechanic/reward/RewardManager.h"
#include "../../mechanic/selection/ChosenHand.h"
#include <iostream>
#include <sstream>

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
  mechanic::RewardManager rewardManager;
  bool isGameOver;
};

} // namespace system_p
