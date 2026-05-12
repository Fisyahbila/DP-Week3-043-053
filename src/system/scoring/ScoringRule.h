#pragma once
#include "../card/hand.h"
#include "../evaluation/PokerHandType.h"

namespace system_p {
    class PokerHandEvaluator; // Forward declaration

    class ScoringRule {
    public:
        ScoringRule();
        ~ScoringRule();
        int scoreHand(const Hand& hand);

    private:
        int convertRankToScore(PokerHandType rank);
        PokerHandEvaluator* evaluator = nullptr;
    };
}