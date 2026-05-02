#include "FlushHouseChecker.h"
#include <iostream>

HandRank FlushHouseChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::FLUSH_HOUSE) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::FLUSH_HOUSE;
}
