#include "GameManager.h"
#include "../../mechanic/selection/ChosenHand.h"
#include "../../mechanic/selection/SelectionValidator.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

namespace system_p {

GameManager::GameManager() 
    : roundState(4, 4), totalMoney(4), isGameOver(false) {}

void GameManager::runSession() {
    std::cout << "\n==============================================" << std::endl;
    std::cout << "          BALATRO RUN SESSION START           " << std::endl;
    std::cout << "==============================================" << std::endl;
    totalMoney = 4; // Start with $4
    isGameOver = false;

    // We play Ante 1, which has Small Blind (0), Big Blind (1), Boss Blind (2)
    int ante = 1;
    for (int blindIndex = 0; blindIndex < 3; ++blindIndex) {
        if (isGameOver) break;
        
        bool winBlind = playBlind(ante, blindIndex);
        if (!winBlind) {
            std::cout << "\n[GAME OVER] Anda gagal mengalahkan " << blindManager.getCurrentBlindName() << "!" << std::endl;
            isGameOver = true;
            break;
        } else {
            // Reward player
            int score = roundState.getCurrentScore();
            int basePayout = (blindIndex == 0) ? 3 : ((blindIndex == 1) ? 4 : 5);
            int handsRemainingBonus = roundState.getHandsRemaining();
            int totalEarned = basePayout + handsRemainingBonus;
            totalMoney += totalEarned;
            
            std::cout << "\n==============================================" << std::endl;
            std::cout << "[MENANG] Anda berhasil mengalahkan " << blindManager.getCurrentBlindName() << "!" << std::endl;
            std::cout << "Detail Hadiah:" << std::endl;
            std::cout << "  - Base Payout: $" << basePayout << std::endl;
            std::cout << "  - Sisa Hand Bonus: $" << handsRemainingBonus << " ($1 per sisa hand)" << std::endl;
            std::cout << "  - Uang Didapat: $" << totalEarned << std::endl;
            std::cout << "  - Total Uang Sekarang: $" << totalMoney << std::endl;
            std::cout << "==============================================\n" << std::endl;
            
            // Trigger shop prompt
            std::cout << "=== TOKO (SHOP) ===" << std::endl;
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
                if (totalMoney >= 3) {
                    totalMoney -= 3;
                    std::cout << "\nPilih kombinasi kartu untuk di-upgrade:" << std::endl;
                    std::cout << "1. High Card" << std::endl;
                    std::cout << "2. Pair" << std::endl;
                    std::cout << "3. Two Pair" << std::endl;
                    std::cout << "4. Three of a Kind" << std::endl;
                    std::cout << "5. Straight" << std::endl;
                    std::cout << "6. Flush" << std::endl;
                    std::cout << "7. Full House" << std::endl;
                    std::cout << "Pilihan (1-7): ";
                    int upgradeChoice = 1;
                    std::cin >> upgradeChoice;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    
                    PokerHandType typeToUpgrade = PokerHandType::HIGH_CARD;
                    switch (upgradeChoice) {
                        case 1: typeToUpgrade = PokerHandType::HIGH_CARD; break;
                        case 2: typeToUpgrade = PokerHandType::PAIR; break;
                        case 3: typeToUpgrade = PokerHandType::TWO_PAIR; break;
                        case 4: typeToUpgrade = PokerHandType::THREE_OF_A_KIND; break;
                        case 5: typeToUpgrade = PokerHandType::STRAIGHT; break;
                        case 6: typeToUpgrade = PokerHandType::FLUSH; break;
                        case 7: typeToUpgrade = PokerHandType::FULL_HOUSE; break;
                        default: typeToUpgrade = PokerHandType::HIGH_CARD; break;
                    }
                    scoringRule.getScoreTable().upgradeHand(typeToUpgrade);
                    std::cout << "[Shop] Berhasil meng-upgrade level " << scoringRule.getScoreTable().getHandName(typeToUpgrade) << "!" << std::endl;
                } else {
                    std::cout << "[Shop] Uang tidak cukup!" << std::endl;
                }
            }
            std::cout << "\nLanjut ke Blind berikutnya...\n" << std::endl;
        }
    }
    
    if (!isGameOver) {
        std::cout << "\n==============================================" << std::endl;
        std::cout << "SELAMAT! Anda telah mengalahkan Ante 1!" << std::endl;
        std::cout << "Total Uang Akhir: $" << totalMoney << std::endl;
        std::cout << "==============================================\n" << std::endl;
    }
}

bool GameManager::playBlind(int ante, int blindIndex) {
    blindManager.selectBlind(ante, blindIndex);
    roundState.reset();
    deck = Deck::createStandardDeck();
    deck.shuffle();
    handState.clear();
    
    // Draw initial 8 cards
    handState.addCards(deck.draw(8));
    
    std::cout << "==============================================" << std::endl;
    std::cout << "MEMULAI BLIND: " << blindManager.getCurrentBlindName() << std::endl;
    std::cout << "Target Score: " << blindManager.getCurrentTargetScore() << std::endl;
    std::cout << "==============================================" << std::endl;
    
    mechanic::SelectionValidator validator;
    
    while (roundState.getHandsRemaining() > 0 && roundState.getCurrentScore() < blindManager.getCurrentTargetScore()) {
        std::cout << "\n----------------------------------------------" << std::endl;
        std::cout << "Blind: " << blindManager.getCurrentBlindName() 
                  << " | Target: " << blindManager.getCurrentTargetScore()
                  << " | Skor Saat Ini: " << roundState.getCurrentScore() << std::endl;
        std::cout << "Sisa Hand: " << roundState.getHandsRemaining() 
                  << " | Sisa Discard: " << roundState.getDiscardsRemaining() << std::endl;
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
        
        std::cin.ignore(10000, '\n'); // Clear trailing characters
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
            // Play Hand
            Hand playedHand;
            const Hand& currentHand = handState.getHand();
            for (int idx : selectedIndices) {
                playedHand.push_back(currentHand[idx]);
            }
            
            // Calculate score using ScoringRule
            int scoredPoints = scoringRule.scoreHand(playedHand);
            roundState.addScore(scoredPoints);
            roundState.useHand();
            
            // Remove played cards
            handState.removeCards(selectedIndices);
            
            // Replenish hand up to 8 cards
            int currentSize = handState.getHand().size();
            if (currentSize < 8) {
                handState.addCards(deck.draw(8 - currentSize));
            }
            
            std::cout << "\n[PLAY] Anda memainkan hand tersebut dan mendapatkan " << scoredPoints << " poin!" << std::endl;
            
        } else if (action == 2) {
            // Discard
            if (roundState.getDiscardsRemaining() <= 0) {
                std::cout << "[DISCARD] Gagal! Sisa discard Anda sudah habis!" << std::endl;
                continue;
            }
            
            roundState.useDiscard();
            
            // Remove discarded cards
            handState.removeCards(selectedIndices);
            
            // Draw replacement cards
            int currentSize = handState.getHand().size();
            if (currentSize < 8) {
                handState.addCards(deck.draw(8 - currentSize));
            }
            
            std::cout << "\n[DISCARD] Kartu berhasil dibuang dan diganti dengan yang baru." << std::endl;
        }
    }
    
    // Check win / loss target
    return blindManager.isTargetMet(roundState.getCurrentScore());
}

void GameManager::printHand() {
    const Hand& hand = handState.getHand();
    std::cout << "Kartu di tangan Anda:" << std::endl;
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << "  [" << i << "] ";
        // Rank
        int r = hand[i].rank;
        if (r == 1) std::cout << "Ace";
        else if (r == 11) std::cout << "Jack";
        else if (r == 12) std::cout << "Queen";
        else if (r == 13) std::cout << "King";
        else std::cout << r;
        
        std::cout << " of ";
        
        // Suit
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
