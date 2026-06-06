#include "FlushHouseChecker.h"
#include <iostream>
#include <map>

namespace system_p {

static std::map<int, int> getRankCounts(const Hand& hand)
{
  std::map<int, int> counts;
  for (const auto& card : hand)
    counts[card.rank]++;
  return counts;
}

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

PokerHandType FlushHouseChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Flush House..." << std::endl;
  if (isFlush(hand)) {
    auto counts = getRankCounts(hand);
    bool hasThree = false, hasTwo = false;
    for (std::map<int,int>::const_iterator it = counts.begin(); it != counts.end(); ++it) {
      if (it->second >= 3)
        hasThree = true;
      else if (it->second >= 2)
        hasTwo = true;
    }
    if (hasThree && hasTwo)
      return PokerHandType::FLUSH_HOUSE;
  }
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p
