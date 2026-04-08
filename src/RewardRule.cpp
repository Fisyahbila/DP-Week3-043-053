#include "RewardRule.h"
#include <iostream>

int RewardRule::earnMoney(bool win, int score)
{
  std::cout << "[Reward Rule] Menghitung hadiah uang..." << std::endl;

  if (win) {
    return score * 2;
  } else {
    return 0;
  }
}