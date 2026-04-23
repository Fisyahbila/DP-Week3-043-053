#include "RewardRule.h"
#include <iostream>

int RewardRule::earnMoney(bool win, int score)
{
  std::cout << "[RewardRule] Calculating reward - win: " << win << ", score: " << score
            << std::endl;
  return win ? score * 10 : 0;
}