#include "FullHouseChecker.h"
#include <iostream>

HandRank FullHouseChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::FULL_HOUSE) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::FULL_HOUSE;
}
