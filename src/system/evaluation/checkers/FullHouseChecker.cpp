#include "FullHouseChecker.h"
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

PokerHandType FullHouseChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Full House..." << std::endl;
  auto counts = getRankCounts(hand);
  bool hasThree = false, hasTwo = false;
  for (std::map<int,int>::const_iterator it = counts.begin(); it != counts.end(); ++it) {
    if (it->second >= 3)
      hasThree = true;
    else if (it->second >= 2)
      hasTwo = true;
  }
  if (hasThree && hasTwo)
    return PokerHandType::FULL_HOUSE;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p
