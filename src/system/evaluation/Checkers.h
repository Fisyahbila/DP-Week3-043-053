#pragma once
#include "PokerHandChecker.h"

namespace system_p {

    class FlushFiveChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class FlushHouseChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class FiveOfAKindChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class RoyalFlushChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class StraightFlushChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class FourOfAKindChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class FullHouseChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class FlushChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class StraightChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class ThreeOfAKindChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class TwoPairChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class PairChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

    class HighCardChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

} // namespace system_p
