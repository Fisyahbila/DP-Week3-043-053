#include "HighCardChecker.h"
#include <iostream>

HandRank HighCardChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::HIGH_CARD) << "..."
            << std::endl;
  return HandRank::HIGH_CARD;
}
