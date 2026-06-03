#ifndef SCORING_RULE_H
#define SCORING_RULE_H

#include "../card/Card.h"
#include "../evaluation/PokerHandType.h"
#include "HandScoreTable.h"
#include "PlayedHandResult.h"

namespace system_p {
    class PokerHandEvaluator; // Forward declaration

    class ScoringRule {
    public:
        ScoringRule();
        ~ScoringRule();
        
        int scoreHand(const Hand& hand);
        PlayedHandResult evaluateAndScore(const Hand& hand);
        HandScoreTable& getScoreTable();

    private:
        PokerHandEvaluator* evaluator = nullptr;
        HandScoreTable scoreTable;
    };
}

#endif // SCORING_RULE_H