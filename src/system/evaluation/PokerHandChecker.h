#pragma once
#include "../card/hand.h"
#include "PokerHandType.h"

namespace system_p {
    class PokerHandChecker {
    public:
        virtual PokerHandType check(const Hand& hand) = 0;
        void setNext(PokerHandChecker* next);
        virtual ~PokerHandChecker() = default;

    protected:
        PokerHandChecker* nextChecker = nullptr;
    };
}