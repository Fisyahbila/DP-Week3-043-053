#include "FiveOfAKindChecker.h"
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

PokerHandType FiveOfAKindChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Five of a Kind..." << std::endl;
  auto counts = getRankCounts(hand);
  for (std::map<int,int>::const_iterator it = counts.begin(); it != counts.end(); ++it)
    if (it->second >= 5)
      return PokerHandType::FIVE_OF_A_KIND;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p
