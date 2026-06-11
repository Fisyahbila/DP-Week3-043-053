#include "mechanic/reward/RewardCommand.h"
#include "mechanic/selection/ChosenHand.h"
#include "mechanic/selection/SelectionValidator.h"
#include "system/blind/BlindManager.h"
#include "system/card/Deck.h"
#include "system/card/HandState.h"
#include "system/scoring/HandScoreTable.h"
#include "system/scoring/ScoringRule.h"
#include "system/blind/BlindManager.h"
#include "system/blind/SmallBlindState.h"
#include "system/blind/BigBlindState.h"
#include "system/blind/BossBlindState.h"
#include "system/run/RoundState.h"
#include "system/run/RunSessionService.h"
#include "system/run/RunSessionState.h"
#include "system/scoring/HandScoreTable.h"
#include "system/scoring/ScoringRule.h"
#include <cassert>
#include <iostream>

using namespace system_p;
using namespace mechanic;

// Test Suite 1: Deck and Drawing
void testDeckAndDrawing()
{
  std::cout << "[TEST] Running Deck & Drawing tests..." << std::endl;
  Deck deck = Deck::createStandardDeck();

  // Draw 8 cards
  Hand hand = deck.draw(8);
  assert(hand.size() == 8);

  // Draw 1 card using drawCard
  Card singleCard = deck.drawCard();
  assert(singleCard.rank >= 1 && singleCard.rank <= 13);

  // Draw remaining cards (52 - 8 - 1 = 43)
  Hand rest = deck.draw(43);
  assert(rest.size() == 43);

  // Empty deck draw
  Hand emptyDraw = deck.draw(1);
  assert(emptyDraw.empty());

  Card emptyCard = deck.drawCard();
  assert(emptyCard.rank == 0); // Default constructed dummy rank

  std::cout << "[PASS] Deck & Drawing tests completed successfully." << std::endl;
}

// Test Suite 2: Hand Selection Validation
void testHandSelection()
{
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
void testScoringSystem()
{
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
void testPolymorphicBlinds()
{
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
  manager.selectBlind(2, 2); // Ante 2, Boss Blind (target 600 * 2 = 1200)
  assert(manager.getCurrentBlindName() == "Boss Blind");
  assert(manager.getCurrentTargetScore() == 1200);
  assert(!manager.isTargetMet(1199));
  assert(manager.isTargetMet(1200));

  std::cout << "[PASS] Polymorphic Blinds tests completed successfully." << std::endl;
}

// Test Suite 5: Round State Management
void testRoundState()
{
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

// Test Suite 6: RunSessionState and RunSessionService
void testRunSessionState()
{
  std::cout << "[TEST] Running RunSessionState tests..." << std::endl;
  RunSessionState sessionState;
  sessionState.persistentState.ante = 2;
  sessionState.persistentState.money = 10;
  sessionState.runtimeState.blindScore = 1500;

  assert(sessionState.persistentState.ante == 2);
  assert(sessionState.persistentState.money == 10);
  assert(sessionState.runtimeState.blindScore == 1500);

  std::cout << "[PASS] RunSessionState tests completed successfully." << std::endl;
}

// Test Suite 7: Skip Reward Commands
void testSkipRewardCommands()
{
  std::cout << "[TEST] Running Skip Reward Commands tests..." << std::endl;

  // --- BonusHandCommand ---
  // Memastikan +1 remainingPlays ditambahkan ke variabel yang direferensikan
  {
    int remainingPlays = 3;
    BonusHandCommand bonusHand(remainingPlays);

    bool result = bonusHand.execute();
    assert(result == true);
    assert(remainingPlays == 4); // 3 + 1

    // Eksekusi kedua: pastikan terus bertambah
    bonusHand.execute();
    assert(remainingPlays == 5);
  }

  // --- FreePlayingCardCommand ---
  // Memastikan kartu baru ditambahkan ke deck (ukuran deck bertambah)
  {
    Deck deck = Deck::createStandardDeck(); // 52 kartu
    int sizeBefore = 0;
    // Hitung ukuran awal dengan draw semua, lalu recreate
    deck = Deck::createStandardDeck();

    // Draw semua 52 kartu agar kita tahu ukuran awal
    Hand allCards = deck.draw(52);
    assert(allCards.size() == 52);

    // Deck kosong, tambahkan satu kartu via FreePlayingCardCommand
    FreePlayingCardCommand freeCard(deck);
    bool result = freeCard.execute();
    assert(result == true);

    // Deck seharusnya sekarang memiliki tepat 1 kartu
    Hand afterAdd = deck.draw(1);
    assert(afterAdd.size() == 1);
    assert(afterAdd[0].rank >= 2 && afterAdd[0].rank <= 14); // rank valid

    // Deck kosong setelah draw 1
    Hand shouldBeEmpty = deck.draw(1);
    assert(shouldBeEmpty.empty());
  }

  // --- FreeRerollCommand ---
  // Memastikan +1 freeRerolls ditambahkan ke variabel yang direferensikan
  {
    int freeRerolls = 0;
    FreeRerollCommand freeReroll(freeRerolls);

    bool result = freeReroll.execute();
    assert(result == true);
    assert(freeRerolls == 1); // 0 + 1

    // Eksekusi kedua: pastikan terus bertambah
    freeReroll.execute();
    assert(freeRerolls == 2);
  }

  std::cout << "[PASS] Skip Reward Commands tests completed successfully." << std::endl;
// Test Suite 7: Skip Blind and Skip Reward Commands
void testSkipBlind() {
    std::cout << "[TEST] Running Skip Blind tests..." << std::endl;
    
    // 1. Test Small Blind Skip Reward
    {
        std::shared_ptr<BlindState> sb = std::make_shared<SmallBlindState>();
        int bonusHands = 0;
        Deck deck = Deck::createStandardDeck();
        int freeRerolls = 0;
        
        auto skipCmd = sb->createSkipRewardCommand(bonusHands, deck, freeRerolls);
        assert(skipCmd != nullptr);
        assert(skipCmd->timing == mechanic::CommandTiming::NextBlind);
        
        // Execute reward command
        bool success = skipCmd->command->execute();
        assert(success);
        assert(bonusHands == 1);
    }
    
    // 2. Test Big Blind Skip Reward
    {
        std::shared_ptr<BlindState> bb = std::make_shared<BigBlindState>();
        int bonusHands = 0;
        Deck deck = Deck::createStandardDeck();
        int freeRerolls = 0;
        int initialDeckSize = deck.draw(52).size(); // draw all to empty it
        deck = Deck::createStandardDeck(); // recreate standard deck (52 cards)
        
        auto skipCmd = bb->createSkipRewardCommand(bonusHands, deck, freeRerolls);
        assert(skipCmd != nullptr);
        assert(skipCmd->timing == mechanic::CommandTiming::Start);
        
        bool success = skipCmd->command->execute();
        assert(success);
        // FreePlayingCardCommand draws 1 card from deck, leaving 51 cards
        assert(deck.draw(52).size() == 51);
    }
    
    // 3. Test Boss Blind Skip Reward
    {
        std::shared_ptr<BlindState> boss = std::make_shared<BossBlindState>();
        int bonusHands = 0;
        Deck deck = Deck::createStandardDeck();
        int freeRerolls = 0;
        
        auto skipCmd = boss->createSkipRewardCommand(bonusHands, deck, freeRerolls);
        assert(skipCmd != nullptr);
        assert(skipCmd->timing == mechanic::CommandTiming::NextShop);
        
        bool success = skipCmd->command->execute();
        assert(success);
        assert(freeRerolls == 1);
    }
    
    std::cout << "[PASS] Skip Blind tests completed successfully." << std::endl;
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
    testRunSessionState();
    testSkipBlind();
    
    std::cout << "==============================================" << std::endl;
    std::cout << "      ALL TESTS PASSED SUCCESSFULLY!          " << std::endl;
    std::cout << "==============================================" << std::endl;
    return 0;
}

int main()
{
  std::cout << "==============================================" << std::endl;
  std::cout << "      BALATRO TDD UNIT TEST SUITE RUNNER      " << std::endl;
  std::cout << "==============================================" << std::endl;

  testDeckAndDrawing();
  testHandSelection();
  testScoringSystem();
  testPolymorphicBlinds();
  testRoundState();
  testRunSessionState();
  testSkipRewardCommands();

  std::cout << "==============================================" << std::endl;
  std::cout << "      ALL TESTS PASSED SUCCESSFULLY!          " << std::endl;
  std::cout << "==============================================" << std::endl;
  return 0;
}