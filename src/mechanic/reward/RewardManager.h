#ifndef REWARD_MANAGER_H
#define REWARD_MANAGER_H

#include "../../system/scoring/HandScoreTable.h"
#include "../joker/JokerManager.h"
#include "../joker/JokerReward.h"
#include "Money.h"
#include "RewardCommand.h"
#include "RewardRule.h"
#include "ShopSystem.h"
#include <iostream>
#include <string>

namespace mechanic {

// RewardManager
// Mengkoordinasi seluruh pipeline reward setelah
// blind clear:
//   1. Hitung reward via RewardRule
//   2. Aplikasikan reward via EarnMoneyCommand
//   3. Buka ShopSystem (Planet Card + Joker)
//
// Memiliki Money, JokerManager, JokerSlot, JokerReward,
// dan ShopSystem secara modular.
class RewardManager {
public:
  RewardManager(system_p::HandScoreTable& scoreTable, int startMoney = 4)
    : money_(startMoney)
    , scoreTable_(scoreTable)
    , jokerSlot_(jokerManager_)
    , jokerReward_(jokerSlot_)
    , shop_(money_, scoreTable_, jokerReward_)
  {
  }

  // Dipanggil setelah pemain menang blind.
  // blindIndex: 0=Small, 1=Big, 2=Boss
  void onBlindCleared(int blindIndex, int handsRemaining, const std::string& blindName)
  {
    int earned = rule_.earnMoney(true, handsRemaining, blindIndex);

    // Command pattern: aplikasikan reward ke money
    EarnMoneyCommand earnCmd(money_, earned);
    earnCmd.execute();

    // Tampilkan detail reward
    printRewardSummary(blindName, rule_.getBasePayout(blindIndex), handsRemaining, earned);

    // Buka toko
    shop_.open();
  }

  // Akses ke JokerManager (untuk attach/notify dari GameManager)
  JokerManager& getJokerManager() { return jokerManager_; }

  int getMoney() const { return money_.getAmount(); }
  Money& getMoneyRef() { return money_; }

private:
  void printRewardSummary(const std::string& blindName,
                          int basePayout,
                          int handsRemainingBonus,
                          int totalEarned) const
  {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "[MENANG] Anda berhasil mengalahkan " << blindName << "!" << std::endl;
    std::cout << "Detail Hadiah:" << std::endl;
    std::cout << "  - Base Payout     : $" << basePayout << std::endl;
    std::cout << "  - Sisa Hand Bonus : $" << handsRemainingBonus << " ($1 per sisa hand)"
              << std::endl;
    std::cout << "  - Uang Didapat    : $" << totalEarned << std::endl;
    std::cout << "  - Total Uang      : $" << money_.getAmount() << std::endl;
    std::cout << "  - Slot Joker      : " << jokerSlot_.usedSlots() << "/" << JokerSlot::MAX_SLOTS
              << std::endl;
    std::cout << "==========================================" << std::endl;
  }

  Money money_;
  RewardRule rule_;

  // Joker subsystem (urutan deklarasi penting: manager sebelum slot/reward)
  JokerManager jokerManager_;
  JokerSlot jokerSlot_;
  JokerReward jokerReward_;

  system_p::HandScoreTable& scoreTable_;
  ShopSystem shop_;
};

} // namespace mechanic

#endif // REWARD_MANAGER_H