#include "StraightFlushChecker.h"
#include <iostream>

HandRank StraightFlushChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::STRAIGHT_FLUSH) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::STRAIGHT_FLUSH;
}
