#include "PokerHandEvaluator.h"
#include "Checkers.h"

namespace system_p {

    PokerHandEvaluator::PokerHandEvaluator() {
        // Priority order (high -> low):
        // Royal Flush > Straight Flush > Flush Five > Five of a Kind >
        // Four of a Kind > Full House > Flush > Straight >
        // Three of a Kind > Two Pair > Pair > High Card

        checkers.push_back(new RoyalFlushChecker());
        checkers.push_back(new StraightFlushChecker());
        checkers.push_back(new FlushFiveChecker());
        checkers.push_back(new FiveOfAKindChecker());
        checkers.push_back(new FourOfAKindChecker());
        checkers.push_back(new FullHouseChecker());
        checkers.push_back(new FlushChecker());
        checkers.push_back(new StraightChecker());
        checkers.push_back(new ThreeOfAKindChecker());
        checkers.push_back(new TwoPairChecker());
        checkers.push_back(new PairChecker());
        checkers.push_back(new HighCardChecker());

        // Build the chain
        for (size_t i = 0; i < checkers.size() - 1; ++i) {
            checkers[i]->setNext(checkers[i + 1]);
        }

        chainHead = checkers[0];
    }

    PokerHandEvaluator::~PokerHandEvaluator() {
        for (auto checker : checkers) {
            delete checker;
        }
    }

    PokerHandType PokerHandEvaluator::evaluate(const Hand& hand) {
        if (chainHead != nullptr) {
            return chainHead->check(hand);
        }
        return PokerHandType::NONE;
    }

} // namespace system_p
