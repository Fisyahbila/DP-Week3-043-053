#include "PairChecker.h"
#include <iostream>

HandRank PairChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::PAIR) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::PAIR;
}
