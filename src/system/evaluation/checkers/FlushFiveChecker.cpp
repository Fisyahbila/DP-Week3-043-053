#include "FlushFiveChecker.h"
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

PokerHandType FlushFiveChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Flush Five..." << std::endl;
  auto counts = getRankCounts(hand);
  bool hasFiveOfAKind = false;
  for (std::map<int,int>::const_iterator it = counts.begin(); it != counts.end(); ++it)
    if (it->second >= 5) {
      hasFiveOfAKind = true;
      break;
    }
  if (hasFiveOfAKind && isFlush(hand))
    return PokerHandType::FLUSH_FIVE;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p
