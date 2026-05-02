#include "FourOfAKindChecker.h"
#include <iostream>

HandRank FourOfAKindChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::FOUR_OF_A_KIND) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::FOUR_OF_A_KIND;
}
