#ifndef POKER_HAND_EVALUATOR_H
#define POKER_HAND_EVALUATOR_H

#include "PokerHandType.h"
#include "PokerHandChecker.h"
#include "../card/hand.h"
#include <vector>

namespace system_p {

    class PokerHandEvaluator {
    public:
        PokerHandEvaluator();
        ~PokerHandEvaluator();

        PokerHandType evaluate(const Hand& hand);

    private:
        PokerHandChecker* chainHead = nullptr;
        std::vector<PokerHandChecker*> checkers;
    };

} // namespace system_p

#endif // POKER_HAND_EVALUATOR_H
