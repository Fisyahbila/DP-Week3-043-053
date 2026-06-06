#include "FlushChecker.h"
#include <iostream>

namespace system_p {

static bool isFlush(const Hand& hand)
{
  if (hand.empty())
    return false;
  Suit first = hand[0].suit;
  for (const auto& card : hand)
    if (card.suit != first)
      return false;
  return true;
}

PokerHandType FlushChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Flush..." << std::endl;
  if (isFlush(hand))
    return PokerHandType::FLUSH;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p