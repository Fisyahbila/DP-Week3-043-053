#pragma once
#include "../card/hand.h"
#include "../evaluation/PokerHandChecker.h"

class ScoringRule {
public:
  ScoringRule();
  int scoreHand(const Hand& hand);

private:
  int convertRankToScore(HandRank rank);

  PokerHandChecker* chainHead = nullptr;
};