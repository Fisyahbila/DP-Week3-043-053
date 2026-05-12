#include "GameManager.h"
#include <iostream>

namespace system_p {

void GameManager::runSession()
{
  std::cout << "\n=== BALATRO ===" << std::endl;

  // 1. Inisialisasi Deck dan Draw Kartu
  deck = Deck::createStandardDeck();
  deck.shuffle();
  std::cout << "[DRAW] Menarik 8 kartu dari deck..." << std::endl;
  handState.addCards(deck.draw(8));

  // 2. Cek jenis & hitung score
  // Menggunakan semua kartu di handState sebagai contoh Minimal Vertical Slice
  int finalScore = scoringRule.scoreHand(handState.getHand());
  std::cout << "[Game Manager] Skor akhir pemain: " << finalScore << std::endl;

  // 3. Cek score terhadap blind target
  bool isWin = blindRule.checkBlind(finalScore);
  std::cout << "[Game Manager] Hasil: " << (isWin ? "MENANG" : "KALAH") << std::endl;

  // 4. Rewarding (Mechanic Domain Stub)
  int money = rewardRule.earnMoney(isWin, finalScore);
  std::cout << "[Game Manager] Total uang yang didapat: $" << money << std::endl;

  std::cout << "=== SESI SELESAI ===\n" << std::endl;
}

} // namespace system_p
