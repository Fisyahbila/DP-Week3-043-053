#pragma once
#include "../../hand.h"

class PokerHandChecker {
public:
    virtual HandRank check(const Hand& hand) = 0;
    void setNext(PokerHandChecker* next);
    virtual ~PokerHandChecker() = default;

protected:
    PokerHandChecker* nextChecker = nullptr;
};