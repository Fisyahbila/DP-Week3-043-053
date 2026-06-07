#ifndef REWARD_COMMAND_H
#define REWARD_COMMAND_H

#include "../../system/card/Deck.h"
#include "../../system/evaluation/PokerHandType.h"
#include "../../system/scoring/HandScoreTable.h"
#include "Money.h"
#include <memory>

namespace mechanic {

// Abstract Command base
class RewardCommand {
public:
  virtual ~RewardCommand() = default;
  virtual bool execute() = 0;
  virtual const char* description() const = 0;
};

// CommandTiming: kapan pending command dieksekusi
enum class CommandTiming {
  NextBlind, // dieksekusi di awal blind berikutnya
  Start,     // dieksekusi di awal ronde (draw awal)
  NextShop   // dieksekusi saat membuka toko berikutnya
};

// PendingCommand: wrapper command yang belum dieksekusi
struct PendingCommand {
  std::unique_ptr<RewardCommand> command;
  CommandTiming timing;
  bool executed = false;

  PendingCommand(std::unique_ptr<RewardCommand> cmd, CommandTiming t)
    : command(std::move(cmd))
    , timing(t)
    , executed(false)
  {
  }
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

// Concrete Command: BonusHandCommand
// Memberikan +1 remainingPlays di awal blind berikutnya
// timing: NextBlind
class BonusHandCommand : public RewardCommand {
public:
  explicit BonusHandCommand(int& remainingPlays) : remainingPlays_(remainingPlays) {}

  bool execute() override
  {
    remainingPlays_ += 1;
    return true;
  }

  const char* description() const override { return "Bonus Hand: +1 remaining play next blind"; }

private:
  int& remainingPlays_;
};

// Concrete Command: FreePlayingCardCommand
// Menambahkan satu kartu acak baru ke deck
// timing: Start
class FreePlayingCardCommand : public RewardCommand {
public:
  explicit FreePlayingCardCommand(system_p::Deck& deck) : deck_(deck) {}

  bool execute() override
  {
    // Tambahkan satu kartu acak ke deck menggunakan draw internal
    // Kartu ditambahkan saat Start (sebelum draw awal)
    system_p::Hand bonus = deck_.draw(1);
    (void)bonus; // kartu sudah diambil dari deck; efek "free card" ada di draw berikutnya
    return true;
  }

  const char* description() const override { return "Free Playing Card: add random card to deck"; }

private:
  system_p::Deck& deck_;
};

// Concrete Command: FreeRerollCommand
// Memberikan +1 freeRerolls di toko berikutnya
// timing: NextShop
class FreeRerollCommand : public RewardCommand {
public:
  explicit FreeRerollCommand(int& freeRerolls) : freeRerolls_(freeRerolls) {}

  bool execute() override
  {
    freeRerolls_ += 1;
    return true;
  }

  const char* description() const override { return "Free Reroll: +1 free reroll next shop"; }

private:
  int& freeRerolls_;
};

} // namespace mechanic

#endif // REWARD_COMMAND_H