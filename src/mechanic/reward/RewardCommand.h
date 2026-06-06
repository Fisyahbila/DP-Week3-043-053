#ifndef REWARD_COMMAND_H
#define REWARD_COMMAND_H

#include "../../system/evaluation/PokerHandType.h"
#include "../../system/scoring/HandScoreTable.h"
#include "Money.h"

namespace mechanic {

// Abstract Command base
class RewardCommand {
public:
  virtual ~RewardCommand() = default;
  virtual bool execute() = 0;
  virtual const char* description() const = 0;
};

// Concrete Command: Earn money (after blind win)
class EarnMoneyCommand : public RewardCommand {
public:
  EarnMoneyCommand(Money& money, int amount) : money_(money), amount_(amount) {}

  bool execute() override
  {
    money_.earn(amount_);
    return true;
  }

  const char* description() const override { return "Earn blind reward"; }

private:
  Money& money_;
  int amount_;
};

// Concrete Command: Buy & apply a Planet Card
class BuyPlanetCardCommand : public RewardCommand {
public:
  BuyPlanetCardCommand(Money& money,
                       system_p::HandScoreTable& table,
                       system_p::PokerHandType handType,
                       int cost = 3)
    : money_(money)
    , table_(table)
    , handType_(handType)
    , cost_(cost)
  {
  }

  bool execute() override
  {
    if (!money_.spend(cost_))
      return false;
    table_.upgradeHand(handType_);
    return true;
  }

  const char* description() const override { return "Buy Planet Card"; }

private:
  Money& money_;
  system_p::HandScoreTable& table_;
  system_p::PokerHandType handType_;
  int cost_;
};

// Concrete Command: Skip shop
class SkipShopCommand : public RewardCommand {
public:
  bool execute() override { return true; }
  const char* description() const override { return "Skip shop"; }
};

} // namespace mechanic

#endif // REWARD_COMMAND_H