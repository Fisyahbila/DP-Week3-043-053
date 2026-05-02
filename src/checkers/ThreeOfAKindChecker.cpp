#include "ThreeOfAKindChecker.h"
#include <iostream>

HandRank ThreeOfAKindChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: " << handRankToString(HandRank::THREE_OF_A_KIND) << "..."
            << std::endl;
  if (nextChecker != nullptr) {
    return nextChecker->check(hand);
  }
  return HandRank::THREE_OF_A_KIND;
}
