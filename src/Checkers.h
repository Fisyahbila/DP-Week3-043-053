#pragma once
#include "PokerHandChecker.h"

class FlushFiveChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class FlushHouseChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class FiveOfAKindChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class RoyalFlushChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class StraightFlushChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class FourOfAKindChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class FullHouseChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class FlushChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class StraightChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class ThreeOfAKindChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class TwoPairChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class PairChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};

class HighCardChecker : public PokerHandChecker {
public:
  HandRank check(const Hand& hand) override;
};