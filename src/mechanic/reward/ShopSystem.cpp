#include "ShopSystem.h"
#include "../joker/jokers/ChipBonusJoker.h"
#include "../joker/jokers/MultiplierJoker.h"
#include <iostream>

namespace mechanic {

// Harga item di toko
static constexpr int PLANET_CARD_COST = 3;
static constexpr int JOKER_COST = 5;

// Constructor
ShopSystem::ShopSystem(Money& money, system_p::HandScoreTable& scoreTable, JokerReward& jokerReward)
  : money_(money)
  , scoreTable_(scoreTable)
  , jokerReward_(jokerReward)
{
}

// open() — entry point toko
void ShopSystem::open()
{
  printSeparator();
  std::cout << "=== TOKO (SHOP) ===" << std::endl;
  printSeparator();
  std::cout << "Uang saat ini : $" << money_.getAmount() << std::endl;
  std::cout << "Slot Joker    : " << jokerReward_.usedSlots() << " / " << JokerSlot::MAX_SLOTS
            << " (kosong: " << jokerReward_.freeSlots() << ")" << std::endl;
  printSeparator();
  std::cout << "1. Beli Planet Card  — Upgrade kombinasi kartu ($" << PLANET_CARD_COST << ")"
            << std::endl;
  std::cout << "2. Beli Joker        — Tambah joker aktif ($" << JOKER_COST << ")" << std::endl;
  std::cout << "3. Lewati Toko dan Lanjut ke Blind Berikutnya" << std::endl;
  std::cout << "Pilihan Anda (1-3): ";

  int shopChoice = 3;
  std::cin >> shopChoice;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    shopChoice = 3;
  }

  switch (shopChoice) {
    case 1:  processPlanetCardPurchase(); break;
    case 2:  processJokerPurchase(); break;
    default: {
      SkipShopCommand skip;
      skip.execute();
      std::cout << "[Shop] Melewati toko." << std::endl;
      break;
    }
  }

  std::cout << "\nLanjut ke Blind berikutnya...\n" << std::endl;
}

// processPlanetCardPurchase
void ShopSystem::processPlanetCardPurchase()
{
  if (!money_.canAfford(PLANET_CARD_COST)) {
    std::cout << "[Shop] Uang tidak cukup! Dibutuhkan $" << PLANET_CARD_COST << "." << std::endl;
    return;
  }

  std::cout << "\nPilih kombinasi kartu untuk di-upgrade:" << std::endl;
  std::cout << "1. High Card         (Mercury)" << std::endl;
  std::cout << "2. Pair              (Venus)" << std::endl;
  std::cout << "3. Two Pair          (Earth)" << std::endl;
  std::cout << "4. Three of a Kind   (Mars)" << std::endl;
  std::cout << "5. Straight          (Jupiter)" << std::endl;
  std::cout << "6. Flush             (Saturn)" << std::endl;
  std::cout << "7. Full House        (Uranus)" << std::endl;
  std::cout << "Pilihan (1-7): ";

  int upgradeChoice = 0;
  std::cin >> upgradeChoice;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    upgradeChoice = 0;
  }

  // Factory membuat PlanetCard sesuai pilihan
  PlanetCard* card = PlanetCardFactory::create(upgradeChoice);
  if (card == nullptr) {
    std::cout << "[Shop] Pilihan tidak valid!" << std::endl;
    return;
  }

  // Command mengeksekusi transaksi:
  //   1. Kurangi uang
  //   2. Upgrade hand via PlanetCard::applyTo()
  BuyPlanetCardCommand buyCmd(money_, scoreTable_, card->getTargetHand(), card->getCost());
  if (buyCmd.execute()) {
    // Terapkan modifier PlanetCard ke tabel (level up)
    card->applyTo(scoreTable_);

    std::cout << "[Shop] Berhasil membeli " << card->getName() << " dan meng-upgrade "
              << scoreTable_.getHandName(card->getTargetHand()) << "!" << std::endl;
    std::cout << "[Shop] Uang tersisa: $" << money_.getAmount() << std::endl;
  }
  else {
    std::cout << "[Shop] Transaksi gagal!" << std::endl;
  }

  delete card;
}

// processJokerPurchase
void ShopSystem::processJokerPurchase()
{
  if (!money_.canAfford(JOKER_COST)) {
    std::cout << "[Shop] Uang tidak cukup! Dibutuhkan $" << JOKER_COST << "." << std::endl;
    return;
  }

  if (!jokerReward_.canReceiveJoker()) {
    std::cout << "[Shop] Slot joker penuh (" << JokerSlot::MAX_SLOTS << "/" << JokerSlot::MAX_SLOTS
              << "). Jual atau buang joker terlebih dahulu." << std::endl;
    return;
  }

  std::cout << "\nPilih Joker yang ingin dibeli:" << std::endl;
  std::cout << "1. Chip Bonus Joker  (+50 Chips setiap hand)" << std::endl;
  std::cout << "2. Multiplier Joker  (+4 Mult setiap hand)" << std::endl;
  std::cout << "Pilihan (1-2): ";

  int jokerChoice = 0;
  std::cin >> jokerChoice;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    jokerChoice = 0;
  }

  // Tentukan joker dan nama
  JokerObserver* newJoker = nullptr;
  std::string jokerName;

  switch (jokerChoice) {
    case 1:
      newJoker = new ChipBonusJoker();
      jokerName = "Chip Bonus Joker";
      break;
    case 2:
      newJoker = new MultiplierJoker();
      jokerName = "Multiplier Joker";
      break;
    default: std::cout << "[Shop] Pilihan joker tidak valid!" << std::endl; return;
  }

  // Kurangi uang terlebih dahulu
  if (!money_.spend(JOKER_COST)) {
    std::cout << "[Shop] Transaksi gagal!" << std::endl;
    delete newJoker;
    return;
  }

  // Command: berikan joker ke slot pemain
  JokerRewardCommand jokerCmd(newJoker, jokerReward_, jokerName);
  if (jokerCmd.execute()) {
    std::cout << "[Shop] Berhasil membeli " << jokerName << "!" << std::endl;
    std::cout << "[Shop] Uang tersisa: $" << money_.getAmount() << std::endl;
    std::cout << "[Shop] Slot joker: " << jokerReward_.usedSlots() << "/" << JokerSlot::MAX_SLOTS
              << std::endl;
  }
  else {
    // Jika grant gagal, kembalikan uang (rollback sederhana)
    money_.earn(JOKER_COST);
    std::cout << "[Shop] Gagal menambahkan joker. Uang dikembalikan." << std::endl;
  }
}

// Helper
void ShopSystem::printSeparator()
{
  std::cout << "==========================================" << std::endl;
}

} // namespace mechanic