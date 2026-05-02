#include "FiveOfAKindChecker.h"
#include <iostream>

HandRank FiveOfAKindChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::FIVE_OF_A_KIND) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::FIVE_OF_A_KIND;
}
