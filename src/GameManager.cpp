#include "GameManager.h"
#include <iostream>

void GameManager::runSession()
{
  std::cout << "\n=== BALATRO ===" << std::endl;

  // 1. siapin kartu
  Hand playerHand = handPlayer.generatehand();
  Hand generatedHand = handGenerator.generateHand();

  // 2. hitung score
  int finalScore = scoringRule.scoreHand(playerHand);
  std::cout << "[Game Manager] Skor akhir pemain: " << finalScore << std::endl;

  // 3. cek blind
  bool isWin = blindRule.checkBlind(finalScore);
  std::cout << "[Game Manager] Hasil: " << (isWin ? "MENANG" : "KALAH") << std::endl;

  // 4. rewarding
  int money = rewardRule.earnMoney(isWin, finalScore);
  std::cout << "[Game Manager] Total uang yang didapat: $" << money << std::endl;

  std::cout << "=== SESI SELESAI ===\n" << std::endl;
}