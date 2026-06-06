#include "StraightChecker.h"
#include <iostream>
#include <set>
#include <vector>

namespace system_p {

static std::vector<int> getSortedUniqueRanks(const Hand& hand)
{
  std::set<int> rankSet;
  for (const auto& card : hand)
    rankSet.insert(card.rank);
  return std::vector<int>(rankSet.begin(), rankSet.end());
}

static bool isStraight(const Hand& hand)
{
  auto ranks = getSortedUniqueRanks(hand);
  if (ranks.size() < 2)
    return true;
  bool normal = true;
  for (size_t i = 1; i < ranks.size(); i++) {
    if (ranks[i] != ranks[i - 1] + 1) {
      normal = false;
      break;
    }
  }
  if (normal)
    return true;
  if (ranks.back() == 14) {
    std::vector<int> aceLow = ranks;
    aceLow.pop_back();
    aceLow.insert(aceLow.begin(), 1);
    bool low = true;
    for (size_t i = 1; i < aceLow.size(); i++) {
      if (aceLow[i] != aceLow[i - 1] + 1) {
        low = false;
        break;
      }
    }
    if (low)
      return true;
  }
  return false;
}

PokerHandType StraightChecker::check(const Hand& hand)
{
  std::cout << "[Checker] Mengecek: Straight..." << std::endl;
  if (isStraight(hand))
    return PokerHandType::STRAIGHT;
  if (nextChecker != nullptr)
    return nextChecker->check(hand);
  return PokerHandType::NONE;
}

} // namespace system_p