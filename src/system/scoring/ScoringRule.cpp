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
        PokerHandType rank = PokerHandType::NONE;

        if (evaluator != nullptr) {
            rank = evaluator->evaluate(hand);
        }

        std::cout << "[Scoring Rule] Rank found: " << static_cast<int>(rank) << std::endl;

        return convertRankToScore(rank);
    }

    int ScoringRule::convertRankToScore(PokerHandType rank) {
        switch (rank) {
            case PokerHandType::FLUSH_FIVE:      return 1500;
            case PokerHandType::FLUSH_HOUSE:     return 1400;
            case PokerHandType::FIVE_OF_A_KIND:  return 1300;
            case PokerHandType::ROYAL_FLUSH:     return 1200;
            case PokerHandType::STRAIGHT_FLUSH:  return 1100;
            case PokerHandType::FOUR_OF_A_KIND:  return 1000;
            case PokerHandType::FULL_HOUSE:      return 900;
            case PokerHandType::FLUSH:           return 800;
            case PokerHandType::STRAIGHT:        return 700;
            case PokerHandType::THREE_OF_A_KIND: return 600;
            case PokerHandType::TWO_PAIR:        return 500;
            case PokerHandType::PAIR:            return 300;
            case PokerHandType::HIGH_CARD:       return 100;
            default:                             return 0;
        }
    }

} // namespace system_p
