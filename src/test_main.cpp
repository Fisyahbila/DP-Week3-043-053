#include "system/card/Deck.h"
#include "system/card/HandState.h"
#include "system/scoring/HandScoreTable.h"
#include "system/scoring/ScoringRule.h"
#include "system/blind/BlindManager.h"
#include "system/run/RoundState.h"
#include "mechanic/selection/ChosenHand.h"
#include "mechanic/selection/SelectionValidator.h"
#include <cassert>
#include <iostream>

using namespace system_p;
using namespace mechanic;

// Test Suite 1: Deck and Drawing
void testDeckAndDrawing() {
    std::cout << "[TEST] Running Deck & Drawing tests..." << std::endl;
    Deck deck = Deck::createStandardDeck();
    
    // Draw 8 cards
    Hand hand = deck.draw(8);
    assert(hand.size() == 8);
    
    // Draw remaining cards (52 - 8 = 44)
    Hand rest = deck.draw(44);
    assert(rest.size() == 44);
    
    // Empty deck draw
    Hand emptyDraw = deck.draw(1);
    assert(emptyDraw.empty());
    
    std::cout << "[PASS] Deck & Drawing tests completed successfully." << std::endl;
}

// Test Suite 2: Hand Selection Validation
void testHandSelection() {
    std::cout << "[TEST] Running Hand Selection tests..." << std::endl;
    ChosenHand chosen;
    SelectionValidator validator;
    
    // Test 1: Valid selection
    chosen.selectCard(0);
    chosen.selectCard(1);
    chosen.selectCard(2);
    assert(chosen.count() == 3);
    assert(validator.validate(chosen, 8)); // 3 cards from a hand of 8 is valid
    
    // Test 2: Duplicate check
    chosen.selectCard(1); // Should not add duplicate index
    assert(chosen.count() == 3);
    
    // Test 3: Deselect check
    chosen.deselectCard(1);
    assert(chosen.count() == 2);
    
    // Test 4: Too many cards (max is 5)
    chosen.clear();
    for (int i = 0; i < 6; ++i) {
        chosen.selectCard(i);
    }
    assert(!validator.validate(chosen, 8)); // 6 cards is invalid
    
    // Test 5: Out of bounds index
    chosen.clear();
    chosen.selectCard(8); // Hand size is 8, so index 8 is out of bounds
    assert(!validator.validate(chosen, 8));
    
    std::cout << "[PASS] Hand Selection tests completed successfully." << std::endl;
}

// Test Suite 3: Data-Driven Scoring
void testScoringSystem() {
    std::cout << "[TEST] Running Data-Driven Scoring tests..." << std::endl;
    HandScoreTable table;
    
    // Test default score values
    HandScoreEntry highCard = table.getScoreEntry(PokerHandType::HIGH_CARD);
    assert(highCard.baseChips == 10);
    assert(highCard.baseMult == 1);
    assert(highCard.level == 1);
    
    HandScoreEntry royalFlush = table.getScoreEntry(PokerHandType::ROYAL_FLUSH);
    assert(royalFlush.baseChips == 100);
    assert(royalFlush.baseMult == 8);
    
    // Test upgrades (Planet Card logic)
    table.upgradeHand(PokerHandType::HIGH_CARD);
    HandScoreEntry upgradedHighCard = table.getScoreEntry(PokerHandType::HIGH_CARD);
    assert(upgradedHighCard.level == 2);
    assert(upgradedHighCard.baseChips == 20); // 10 + 10
    assert(upgradedHighCard.baseMult == 2);   // 1 + 1
    
    std::cout << "[PASS] Data-Driven Scoring tests completed successfully." << std::endl;
}

// Test Suite 4: Polymorphic Blinds
void testPolymorphicBlinds() {
    std::cout << "[TEST] Running Polymorphic Blinds tests..." << std::endl;
    BlindManager manager;
    
    // Test 1: Small Blind (Ante 1)
    manager.selectBlind(1, 0); // Ante 1, Small Blind
    assert(manager.getCurrentBlindName() == "Small Blind");
    assert(manager.getCurrentTargetScore() == 300);
    assert(!manager.isTargetMet(299));
    assert(manager.isTargetMet(300));
    
    // Test 2: Big Blind (Ante 1)
    manager.selectBlind(1, 1); // Ante 1, Big Blind
    assert(manager.getCurrentBlindName() == "Big Blind");
    assert(manager.getCurrentTargetScore() == 800);
    assert(!manager.isTargetMet(799));
    assert(manager.isTargetMet(800));
    
    // Test 3: Boss Blind (Ante 2)
    manager.selectBlind(2, 2); // Ante 2, Boss Blind (target 1600 * 2 = 3200)
    assert(manager.getCurrentBlindName() == "Boss Blind");
    assert(manager.getCurrentTargetScore() == 3200);
    assert(!manager.isTargetMet(3199));
    assert(manager.isTargetMet(3200));
    
    std::cout << "[PASS] Polymorphic Blinds tests completed successfully." << std::endl;
}

// Test Suite 5: Round State Management
void testRoundState() {
    std::cout << "[TEST] Running Round State tests..." << std::endl;
    RoundState state(4, 4); // 4 hands, 4 discards
    
    assert(state.getHandsRemaining() == 4);
    assert(state.getDiscardsRemaining() == 4);
    assert(state.getCurrentScore() == 0);
    
    // Use hands and discards
    bool handUsed = state.useHand();
    bool discardUsed = state.useDiscard();
    assert(handUsed);
    assert(discardUsed);
    assert(state.getHandsRemaining() == 3);
    assert(state.getDiscardsRemaining() == 3);
    
    // Accumulate score
    state.addScore(150);
    state.addScore(250);
    assert(state.getCurrentScore() == 400);
    
    // Reset round
    state.reset();
    assert(state.getHandsRemaining() == 4);
    assert(state.getDiscardsRemaining() == 4);
    assert(state.getCurrentScore() == 0);
    
    std::cout << "[PASS] Round State tests completed successfully." << std::endl;
}

int main() {
    std::cout << "==============================================" << std::endl;
    std::cout << "      BALATRO TDD UNIT TEST SUITE RUNNER      " << std::endl;
    std::cout << "==============================================" << std::endl;
    
    testDeckAndDrawing();
    testHandSelection();
    testScoringSystem();
    testPolymorphicBlinds();
    testRoundState();
    
    std::cout << "==============================================" << std::endl;
    std::cout << "      ALL TESTS PASSED SUCCESSFULLY!          " << std::endl;
    std::cout << "==============================================" << std::endl;
    return 0;
}
