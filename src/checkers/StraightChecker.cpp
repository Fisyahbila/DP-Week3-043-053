#include "StraightChecker.h"
#include <iostream>

HandRank StraightChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::STRAIGHT) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::STRAIGHT;
}
