#include "TwoPairChecker.h"
#include <iostream>

HandRank TwoPairChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::TWO_PAIR) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::TWO_PAIR;
}
