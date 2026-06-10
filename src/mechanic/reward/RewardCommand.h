#ifndef REWARD_COMMAND_H
#define REWARD_COMMAND_H

#include "../../system/card/Deck.h"
#include "../../system/evaluation/PokerHandType.h"
#include "../../system/scoring/HandScoreTable.h"
#include "../joker/Joker.h"
#include "../joker/JokerReward.h"
#include "Money.h"
#include <memory>
#include <string>
#include <cstdlib>

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
  NextShop,  // dieksekusi saat membuka toko berikutnya
  NextAnte   // dieksekusi saat transisi ke ante berikutnya
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

// EarnMoneyCommand
// Memberikan sejumlah uang kepada pemain (reward blind)
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

// BuyPlanetCardCommand
// Membeli Planet Card dari toko: kurangi uang + upgrade hand
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

// SkipShopCommand
// Tidak melakukan apa-apa; digunakan saat pemain
// memilih untuk melewati toko.
class SkipShopCommand : public RewardCommand {
public:
  bool execute() override { return true; }
  const char* description() const override { return "Skip shop"; }
};

// JokerRewardCommand
// Memberikan Joker baru ke slot aktif pemain.
// Menggunakan JokerReward untuk validasi slot dan
// memanggil attach ke JokerManager.
//
// Ownership joker berpindah ke JokerManager jika
// grantJoker() berhasil. Jika gagal (slot penuh),
// joker di-delete di sini agar tidak leak.
class JokerRewardCommand : public RewardCommand {
public:
  // joker    : concrete joker yang akan diberikan (raw pointer, ownership ke command ini dulu)
  // reward   : JokerReward yang mengelola slot pemain
  // jokerName: nama untuk logging / tampilan
  JokerRewardCommand(JokerObserver* joker, JokerReward& reward, const std::string& jokerName)
    : joker_(joker)
    , reward_(reward)
    , jokerName_(jokerName)
  {
  }

  ~JokerRewardCommand() override
  {
    // Jika execute() belum dipanggil atau gagal dan joker_
    // belum di-transfer ke JokerSlot, kita bersihkan di sini.
    // Setelah execute() sukses joker_ di-set null.
    delete joker_;
  }

  bool execute() override
  {
    if (joker_ == nullptr)
      return false;

    bool ok = reward_.grantJoker(joker_, jokerName_);
    if (ok) {
      joker_ = nullptr; // ownership berpindah ke JokerManager via JokerSlot
    }
    return ok;
  }

  const char* description() const override { return "Grant Joker reward"; }

private:
  JokerObserver* joker_; // nullptr setelah transfer berhasil
  JokerReward& reward_;
  std::string jokerName_;
};

// BonusHandCommand
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

// FreePlayingCardCommand
// Menambahkan satu kartu acak baru ke deck
// timing: Start
class FreePlayingCardCommand : public RewardCommand {
public:
  explicit FreePlayingCardCommand(system_p::Deck& deck) : deck_(deck) {}

  bool execute() override
  {
    // Buat kartu acak: rank 2–14, suit acak
    int rank = 2 + (std::rand() % 13); // rank 2..14
    system_p::Suit suit = static_cast<system_p::Suit>(std::rand() % 4);
    deck_.addCard(system_p::Card(rank, suit));
    return true;
  }

  const char* description() const override { return "Free Playing Card: add random card to deck"; }

private:
  system_p::Deck& deck_;
};

// FreeRerollCommand
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