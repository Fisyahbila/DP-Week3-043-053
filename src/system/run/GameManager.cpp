#include "GameManager.h"
#include "../../mechanic/selection/ChosenHand.h"
#include "../../mechanic/selection/SelectionValidator.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

namespace system_p {

GameManager::GameManager()
  : roundState(4, 4)
  , rewardManager(scoringRule.getScoreTable(), 4)
  , // start $4
  isGameOver(false)
{
}

void GameManager::runSession()
{
  std::cout << "\n==============================================" << std::endl;
  std::cout << "          BALATRO RUN SESSION START           " << std::endl;
  std::cout << "==============================================" << std::endl;
  isGameOver = false;

  int ante = 1;
  for (int blindIndex = 0; blindIndex < 3; ++blindIndex) {
    if (isGameOver)
      break;

    bool winBlind = playBlind(ante, blindIndex);
    if (winBlind) {
      rewardManager.onBlindCleared(blindIndex,
                                   roundState.getHandsRemaining(),
                                   blindManager.getCurrentBlindName());
    }
    else {
      std::cout << "\n[GAME OVER] Anda gagal mengalahkan " << blindManager.getCurrentBlindName()
                << "!" << std::endl;
      isGameOver = true;
    }
  }

  if (!isGameOver) {
    std::cout << "\n==============================================" << std::endl;
    std::cout << "SELAMAT! Anda telah mengalahkan Ante 1!" << std::endl;
    std::cout << "Total Uang Akhir: $" << rewardManager.getMoney() << std::endl;
    std::cout << "==============================================\n" << std::endl;
  }
}

bool GameManager::playBlind(int ante, int blindIndex)
{
  blindManager.selectBlind(ante, blindIndex);
  roundState.reset();
  deck = Deck::createStandardDeck();
  deck.shuffle();
  handState.clear();

  handState.addCards(deck.draw(8));

  std::cout << "==============================================" << std::endl;
  std::cout << "MEMULAI BLIND: " << blindManager.getCurrentBlindName() << std::endl;
  std::cout << "Target Score: " << blindManager.getCurrentTargetScore() << std::endl;
  std::cout << "==============================================" << std::endl;

  mechanic::SelectionValidator validator;

  while (roundState.getHandsRemaining() > 0 &&
         roundState.getCurrentScore() < blindManager.getCurrentTargetScore()) {
    std::cout << "\n----------------------------------------------" << std::endl;
    std::cout << "Blind: " << blindManager.getCurrentBlindName()
              << " | Target: " << blindManager.getCurrentTargetScore()
              << " | Skor Saat Ini: " << roundState.getCurrentScore() << std::endl;
    std::cout << "Sisa Hand: " << roundState.getHandsRemaining()
              << " | Sisa Discard: " << roundState.getDiscardsRemaining() << std::endl;
    std::cout << "Uang Saat Ini: $" << rewardManager.getMoney() << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    printHand();

    std::cout << "\nPilih Aksi:\n";
    std::cout << "  1. Mainkan Tangan (Play Hand)\n";
    std::cout << "  2. Buang Kartu (Discard)\n";
    std::cout << "  3. Keluar dari Game (Quit)\n";
    std::cout << "Aksi (1-3): ";

    int action = 0;
    std::cin >> action;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Input tidak valid. Silakan pilih 1-3." << std::endl;
      continue;
    }

    if (action == 3) {
      std::cout << "Keluar dari sesi Balatro..." << std::endl;
      isGameOver = true;
      return false;
    }

    if (action != 1 && action != 2) {
      std::cout << "Aksi tidak dikenal. Silakan pilih 1 atau 2." << std::endl;
      continue;
    }

    std::cin.ignore(10000, '\n');
    std::cout << "Masukkan indeks kartu (0-7 dipisahkan spasi, misal '0 1 4'): ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    int cardIdx;
    mechanic::ChosenHand chosenHand;
    while (ss >> cardIdx) {
      chosenHand.selectCard(cardIdx);
    }

    int handSize = handState.getHand().size();
    if (!validator.validate(chosenHand, handSize)) {
      std::cout << "Pilihan kartu tidak valid!" << std::endl;
      continue;
    }

    std::vector<int> selectedIndices = chosenHand.getSelectedIndices();

    if (action == 1) {
      Hand playedHand;
      const Hand& currentHand = handState.getHand();
      for (int idx : selectedIndices) {
        playedHand.push_back(currentHand[idx]);
      }

      int scoredPoints = scoringRule.scoreHand(playedHand);
      roundState.addScore(scoredPoints);
      roundState.useHand();

      handState.removeCards(selectedIndices);

      int currentSize = handState.getHand().size();
      if (currentSize < 8) {
        handState.addCards(deck.draw(8 - currentSize));
      }

      std::cout << "\n[PLAY] Anda mendapatkan " << scoredPoints
                << " poin! Total: " << roundState.getCurrentScore() << std::endl;
    }
    else if (action == 2) {
      if (roundState.getDiscardsRemaining() <= 0) {
        std::cout << "[DISCARD] Gagal! Sisa discard Anda sudah habis!" << std::endl;
        continue;
      }

      roundState.useDiscard();
      handState.removeCards(selectedIndices);

      int currentSize = handState.getHand().size();
      if (currentSize < 8) {
        handState.addCards(deck.draw(8 - currentSize));
      }

      std::cout << "\n[DISCARD] Kartu berhasil dibuang dan diganti." << std::endl;
    }
  }

  return blindManager.isTargetMet(roundState.getCurrentScore());
}

void GameManager::printHand()
{
  const Hand& hand = handState.getHand();
  std::cout << "Kartu di tangan Anda:" << std::endl;
  for (size_t i = 0; i < hand.size(); ++i) {
    std::cout << "  [" << i << "] ";
    int r = hand[i].rank;
    if (r == 1)
      std::cout << "Ace";
    else if (r == 11)
      std::cout << "Jack";
    else if (r == 12)
      std::cout << "Queen";
    else if (r == 13)
      std::cout << "King";
    else
      std::cout << r;

    std::cout << " of ";

    switch (hand[i].suit) {
      case Suit::HEART:   std::cout << "Heart (H)"; break;
      case Suit::DIAMOND: std::cout << "Diamond (D)"; break;
      case Suit::CLUB:    std::cout << "Club (C)"; break;
      case Suit::SPADE:   std::cout << "Spade (S)"; break;
    }
    std::cout << std::endl;
  }
}

} // namespace system_p