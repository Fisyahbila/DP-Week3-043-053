#include "ScoringRule.h"
#include "../evaluation/Checkers.h"
#include <iostream>

ScoringRule::ScoringRule()
{
  // 1. Membuat semua instansiasi checker
  PokerHandChecker* flushFive = new FlushFiveChecker();
  PokerHandChecker* flushHouse = new FlushHouseChecker();
  PokerHandChecker* fiveOfAKind = new FiveOfAKindChecker();
  PokerHandChecker* royalFlush = new RoyalFlushChecker();
  PokerHandChecker* straightFlush = new StraightFlushChecker();
  PokerHandChecker* fourOfAKind = new FourOfAKindChecker();
  PokerHandChecker* fullHouse = new FullHouseChecker();
  PokerHandChecker* flush = new FlushChecker();
  PokerHandChecker* straight = new StraightChecker();
  PokerHandChecker* threeOfAKind = new ThreeOfAKindChecker();
  PokerHandChecker* twoPair = new TwoPairChecker();
  PokerHandChecker* pair = new PairChecker();
  PokerHandChecker* highCard = new HighCardChecker();

  // 2. Merangkai Chain of Responsibility
  flushFive->setNext(flushHouse);
  flushHouse->setNext(fiveOfAKind);
  fiveOfAKind->setNext(royalFlush);
  royalFlush->setNext(straightFlush);
  straightFlush->setNext(fourOfAKind);
  fourOfAKind->setNext(fullHouse);
  fullHouse->setNext(flush);
  flush->setNext(straight);
  straight->setNext(threeOfAKind);
  threeOfAKind->setNext(twoPair);
  twoPair->setNext(pair);
  pair->setNext(highCard);

  // 3. Menetapkan chainHead ke pengecek pertama
  chainHead = flushFive;
}

int ScoringRule::scoreHand(const Hand& hand)
{
  HandRank rank = HandRank::NONE;

  if (chainHead != nullptr) {
    rank = chainHead->check(hand);
  }

  std::cout << "[Scoring Rule] Jenis Hand yang Ditemukan: " << handRankToString(rank) << std::endl;

  return convertRankToScore(rank);
}

int ScoringRule::convertRankToScore(HandRank rank)
{
  switch (rank) {
    case HandRank::FLUSH_FIVE:      return 1500;
    case HandRank::FLUSH_HOUSE:     return 1400;
    case HandRank::FIVE_OF_A_KIND:  return 1300;
    case HandRank::ROYAL_FLUSH:     return 1200;
    case HandRank::STRAIGHT_FLUSH:  return 1100;
    case HandRank::FOUR_OF_A_KIND:  return 1000;
    case HandRank::FULL_HOUSE:      return 900;
    case HandRank::FLUSH:           return 800;
    case HandRank::STRAIGHT:        return 700;
    case HandRank::THREE_OF_A_KIND: return 600;
    case HandRank::TWO_PAIR:        return 500;
    case HandRank::PAIR:            return 300;
    case HandRank::HIGH_CARD:       return 100;
    default:                        return 0;
  }
}