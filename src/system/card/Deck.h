#pragma once
#include "Card.h"
#include <vector>

namespace system_p {

class Deck {
public:
  static Deck createStandardDeck();
  void shuffle();
  Hand draw(int count);
  void addCard(const Card& card); // BUG FIX #3: tambah kartu ke deck
private:
  std::vector<Card> cards;
};

} // namespace system_p