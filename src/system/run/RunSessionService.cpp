#include "RunSessionService.h"
#include "../blind/SmallBlindState.h"
#include "../../mechanic/selection/ChosenHand.h"
#include "../../mechanic/selection/SelectionValidator.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

namespace system_p {

RunSessionService::RunSessionService()
  : roundState(4, 4)
  , rewardManager(scoringRule.getScoreTable(), 4)
  , isGameOver(false)
{
    sessionState.persistentState.ante = 1;
    sessionState.persistentState.money = rewardManager.getMoney();
}

void RunSessionService::runSession()
{
  std::cout << "\n==============================================" << std::endl;
  std::cout << "          BALATRO RUN SESSION START           " << std::endl;
  std::cout << "==============================================" << std::endl;
  isGameOver = false;

  int ante = 1;
  sessionState.persistentState.ante = ante;
  sessionState.persistentState.currentBlind = std::make_shared<SmallBlindState>();

  for (int blindIndex = 0; blindIndex < 3; ++blindIndex) {
    if (isGameOver)
      break;

    // Timing hook: NextBlind
    executePendingCommands(mechanic::CommandTiming::NextBlind);

    bool winBlind = playBlind(sessionState.persistentState.ante, blindIndex);
    if (winBlind) {
      // Timing hook: NextShop (before blind cleared/shop opens)
      executePendingCommands(mechanic::CommandTiming::NextShop);

      rewardManager.onBlindCleared(blindIndex,
                                   roundState.getHandsRemaining(),
                                   blindManager.getCurrentBlindName());

      sessionState.persistentState.money = rewardManager.getMoney();

      // Polimorfis transition
      sessionState.persistentState.currentBlind = sessionState.persistentState.currentBlind->extState(sessionState.persistentState.ante);

      if (blindIndex == 2) {
          // Timing hook: NextAnte
          executePendingCommands(mechanic::CommandTiming::NextAnte);
      }
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

bool RunSessionService::playBlind(int ante, int blindIndex)
{
  blindManager.selectBlind(ante, blindIndex);
  drawInitialHand();

  std::cout << "==============================================" << std::endl;
  std::cout << "MEMULAI BLIND: " << blindManager.getCurrentBlindName() << std::endl;
  std::cout << "Target Score: " << blindManager.getCurrentTargetScore() << std::endl;
  std::cout << "==============================================" << std::endl;

  while (sessionState.runtimeState.remainingHands > 0 &&
         sessionState.runtimeState.blindScore < blindManager.getCurrentTargetScore() &&
         !isGameOver) {
    
    printCurrentState();

    int action = readPlayerActionRequest();
    if (action == -1) {
      continue;
    }

    if (!canPerformAction(action)) {
      continue;
    }

    processPlayerAction(action);
  }

  return blindManager.isTargetMet(sessionState.runtimeState.blindScore);
}

void RunSessionService::drawInitialHand()
{
  roundState.reset();
  deck = Deck::createStandardDeck();
  deck.shuffle();
  handState.clear();

  // Execute pending command at Start timing
  executePendingCommands(mechanic::CommandTiming::Start);

  handState.addCards(deck.draw(8));

  // Sync to runtimeState
  sessionState.runtimeState.blindScore = roundState.getCurrentScore();
  sessionState.runtimeState.remainingHands = roundState.getHandsRemaining();
  sessionState.runtimeState.remainingDiscards = roundState.getDiscardsRemaining();
}

void RunSessionService::printCurrentState()
{
  std::cout << "\n----------------------------------------------" << std::endl;
  std::cout << "Blind: " << blindManager.getCurrentBlindName()
            << " | Target: " << blindManager.getCurrentTargetScore()
            << " | Skor Saat Ini: " << sessionState.runtimeState.blindScore << std::endl;
  std::cout << "Sisa Hand: " << sessionState.runtimeState.remainingHands
            << " | Sisa Discard: " << sessionState.runtimeState.remainingDiscards << std::endl;
  std::cout << "Uang Saat Ini: $" << sessionState.persistentState.money << std::endl;
  std::cout << "----------------------------------------------" << std::endl;

  printHand();
}

int RunSessionService::readPlayerActionRequest()
{
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
    return -1;
  }
  return action;
}

bool RunSessionService::canPerformAction(int action)
{
  if (action == 3) {
    return true;
  }

  if (action != 1 && action != 2) {
    std::cout << "Aksi tidak dikenal. Silakan pilih 1 atau 2." << std::endl;
    return false;
  }

  if (action == 2 && sessionState.runtimeState.remainingDiscards <= 0) {
    std::cout << "[DISCARD] Gagal! Sisa discard Anda sudah habis!" << std::endl;
    return false;
  }

  return true;
}

void RunSessionService::processPlayerAction(int action)
{
  if (action == 3) {
    std::cout << "Keluar dari sesi Balatro..." << std::endl;
    isGameOver = true;
    return;
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

  mechanic::SelectionValidator validator;
  int handSize = handState.getHand().size();
  if (!validator.validate(chosenHand, handSize)) {
    std::cout << "Pilihan kartu tidak valid!" << std::endl;
    return;
  }

  std::vector<int> selectedIndices = chosenHand.getSelectedIndices();

  if (action == 1) {
    Hand playedHand;
    const Hand& currentHand = handState.getHand();
    for (int idx : selectedIndices) {
      playedHand.push_back(currentHand[idx]);
    }

    PlayedHandResult result = scoringRule.evaluateAndScore(playedHand);
    int scoredPoints = rewardManager.getJokerManager().getFinalScore(result);
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
    roundState.useDiscard();
    handState.removeCards(selectedIndices);

    int currentSize = handState.getHand().size();
    if (currentSize < 8) {
      handState.addCards(deck.draw(8 - currentSize));
    }

    std::cout << "\n[DISCARD] Kartu berhasil dibuang dan diganti." << std::endl;
  }

  // Sync state
  sessionState.runtimeState.blindScore = roundState.getCurrentScore();
  sessionState.runtimeState.remainingHands = roundState.getHandsRemaining();
  sessionState.runtimeState.remainingDiscards = roundState.getDiscardsRemaining();
  sessionState.persistentState.money = rewardManager.getMoney();
}

void RunSessionService::executePendingCommands(mechanic::CommandTiming timing)
{
  auto& cmds = sessionState.persistentState.pendingCommands;
  for (auto it = cmds.begin(); it != cmds.end(); ) {
    if (it->timing == timing && !it->executed) {
      std::cout << "[RunSessionService] Executing pending command: " << it->command->description() << std::endl;
      bool success = it->command->execute();
      if (success) {
        it->executed = true;
        it = cmds.erase(it);
        continue;
      } else {
        std::cout << "[RunSessionService] Execution failed for command: " << it->command->description() << std::endl;
      }
    }
    ++it;
  }
}

void RunSessionService::printHand()
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
