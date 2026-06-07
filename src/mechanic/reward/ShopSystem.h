#ifndef SHOP_SYSTEM_H
#define SHOP_SYSTEM_H

#include "../../system/scoring/HandScoreTable.h"
#include "../joker/JokerReward.h"
#include "Money.h"
#include "PlanetCard.h"
#include "PlanetCardFactory.h"
#include "RewardCommand.h"

namespace mechanic {

// ShopSystem
// Mengelola interaksi toko antara pemain dan item
// pasca rintangan (blind) selesai.
//
// Mendukung:
//   - Pembelian Planet Card (upgrade kombinasi kartu)
//   - Pembelian Joker (masuk ke slot aktif pemain)
//   - Skip toko
//
// Menggunakan Command pattern untuk setiap transaksi
// sehingga mudah diperluas dengan item baru.
class ShopSystem {
public:
  ShopSystem(Money& money, system_p::HandScoreTable& scoreTable, JokerReward& jokerReward);

  // Tampilkan menu toko dan proses pilihan pemain
  void open();

private:
  // Sub-alur pembelian
  void processPlanetCardPurchase();
  void processJokerPurchase();

  // Helper menu
  static void printSeparator();

  Money& money_;
  system_p::HandScoreTable& scoreTable_;
  JokerReward& jokerReward_;
};

} // namespace mechanic

#endif // SHOP_SYSTEM_H