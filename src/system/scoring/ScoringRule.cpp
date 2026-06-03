#include "ScoringRule.h"
#include "../evaluation/PokerHandEvaluator.h"
#include <iostream>

namespace system_p {

ScoringRule::ScoringRule() {
    evaluator = new PokerHandEvaluator();
}

ScoringRule::~ScoringRule() {
    delete evaluator;
}

int ScoringRule::scoreHand(const Hand& hand) {
    PlayedHandResult result = evaluateAndScore(hand);
    return result.baseChips * result.baseMult;
}

PlayedHandResult ScoringRule::evaluateAndScore(const Hand& hand) {
    PokerHandType rank = PokerHandType::NONE;
    if (evaluator != nullptr) {
        rank = evaluator->evaluate(hand);
    }

    HandScoreEntry entry = scoreTable.getScoreEntry(rank);
    std::cout << "[Scoring Rule] Hand Type: " << scoreTable.getHandName(rank)
              << " | Level: " << entry.level
              << " | Chips: " << entry.baseChips
              << " | Mult: " << entry.baseMult
              << " | Total: " << (entry.baseChips * entry.baseMult) << std::endl;

    return PlayedHandResult(entry.baseChips, entry.baseMult, rank);
}

HandScoreTable& ScoringRule::getScoreTable() {
    return scoreTable;
}

} // namespace system_p
