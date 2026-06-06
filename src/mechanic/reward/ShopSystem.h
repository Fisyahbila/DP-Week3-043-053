#ifndef SHOP_SYSTEM_H
#define SHOP_SYSTEM_H

#include "../../system/scoring/HandScoreTable.h"
#include "Money.h"
#include "PlanetCard.h"
#include "PlanetCardFactory.h"
#include "RewardCommand.h"
#include <iostream>

namespace mechanic {

// ShopSystem mengelola interaksi toko antara player dan item.
// Menggunakan Command pattern untuk setiap transaksi.
class ShopSystem {
public:
  ShopSystem(Money& money, system_p::HandScoreTable& scoreTable)
    : money_(money)
    , scoreTable_(scoreTable)
  {
  }

  // Tampilkan dan proses interaksi toko
  void open()
  {
    std::cout << "\n=== TOKO (SHOP) ===" << std::endl;
    std::cout << "Uang saat ini: $" << money_.getAmount() << std::endl;
    std::cout << "1. Beli Planet Card: Upgrade Hand ($3)" << std::endl;
    std::cout << "2. Lewati Toko dan Lanjut ke Blind Berikutnya" << std::endl;
    std::cout << "Pilihan Anda (1-2): ";

    int shopChoice = 2;
    std::cin >> shopChoice;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }

    if (shopChoice == 1) {
      processPlanetCardPurchase();
    }
    else {
      SkipShopCommand skip;
      skip.execute();
      std::cout << "[Shop] Melewati toko." << std::endl;
    }

    std::cout << "\nLanjut ke Blind berikutnya...\n" << std::endl;
  }

private:
  void processPlanetCardPurchase()
  {
    if (!money_.canAfford(3)) {
      std::cout << "[Shop] Uang tidak cukup!" << std::endl;
      return;
    }

    std::cout << "\nPilih kombinasi kartu untuk di-upgrade:" << std::endl;
    std::cout << "1. High Card  (Mercury)" << std::endl;
    std::cout << "2. Pair       (Venus)" << std::endl;
    std::cout << "3. Two Pair   (Earth)" << std::endl;
    std::cout << "4. Three of a Kind (Mars)" << std::endl;
    std::cout << "5. Straight   (Jupiter)" << std::endl;
    std::cout << "6. Flush      (Saturn)" << std::endl;
    std::cout << "7. Full House (Uranus)" << std::endl;
    std::cout << "Pilihan (1-7): ";

    int upgradeChoice = 1;
    std::cin >> upgradeChoice;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }

    // Factory membuat PlanetCard sesuai pilihan
    PlanetCard* card = PlanetCardFactory::create(upgradeChoice);
    if (card == nullptr) {
      std::cout << "[Shop] Pilihan tidak valid!" << std::endl;
      return;
    }

    // Command mengeksekusi transaksi (spend money + upgrade)
    BuyPlanetCardCommand buyCmd(money_, scoreTable_, card->getTargetHand(), card->getCost());
    if (buyCmd.execute()) {
      std::cout << "[Shop] Berhasil membeli " << card->getName() << " dan meng-upgrade "
                << scoreTable_.getHandName(card->getTargetHand()) << "!" << std::endl;
      std::cout << "[Shop] Uang tersisa: $" << money_.getAmount() << std::endl;
    }
    else {
      std::cout << "[Shop] Transaksi gagal!" << std::endl;
    }

    delete card;
  }

  Money& money_;
  system_p::HandScoreTable& scoreTable_;
};

} // namespace mechanic

#endif // SHOP_SYSTEM_H