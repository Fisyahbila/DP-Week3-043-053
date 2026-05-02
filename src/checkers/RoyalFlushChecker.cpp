#include "RoyalFlushChecker.h"
#include <iostream>

HandRank RoyalFlushChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::ROYAL_FLUSH) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::ROYAL_FLUSH;
}
