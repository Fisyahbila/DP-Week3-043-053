#include "FlushFiveChecker.h"
#include <iostream>

HandRank FlushFiveChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::FLUSH_FIVE) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::FLUSH_FIVE;
}
