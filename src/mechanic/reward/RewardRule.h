#ifndef REWARD_RULE_H
#define REWARD_RULE_H

namespace mechanic {

// Encapsulates reward calculation logic after a blind is cleared.
// blindIndex: 0 = Small Blind, 1 = Big Blind, 2 = Boss Blind
class RewardRule {
public:
  int earnMoney(bool win, int handsRemaining, int blindIndex = 0) const
  {
    if (!win)
      return 0;
    int basePayout = getBasePayout(blindIndex);
    int bonus = handsRemaining; // $1 per remaining hand
    return basePayout + bonus;
  }

  int getBasePayout(int blindIndex) const
  {
    switch (blindIndex) {
      case 0:  return 3; // Small Blind
      case 1:  return 4; // Big Blind
      case 2:  return 5; // Boss Blind
      default: return 3;
    }
  }
};

} // namespace mechanic

#endif // REWARD_RULE_H