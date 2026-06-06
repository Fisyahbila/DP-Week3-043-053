#include "TwoPairChecker.h"
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

PokerHandType TwoPairChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Two Pair..." << std::endl;
  auto counts = getRankCounts(hand);
  int pairCount = 0;
  for (std::map<int,int>::const_iterator it = counts.begin(); it != counts.end(); ++it)
    if (it->second >= 2)
      pairCount++;
  if (pairCount >= 2)
    return PokerHandType::TWO_PAIR;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p
