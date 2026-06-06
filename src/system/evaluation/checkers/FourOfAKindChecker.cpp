#include "FourOfAKindChecker.h"
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

PokerHandType FourOfAKindChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Four of a Kind..." << std::endl;
  auto counts = getRankCounts(hand);
  for (std::map<int,int>::const_iterator it = counts.begin(); it != counts.end(); ++it)
    if (it->second >= 4)
      return PokerHandType::FOUR_OF_A_KIND;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p
