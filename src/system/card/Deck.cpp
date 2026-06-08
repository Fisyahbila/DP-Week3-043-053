#include "Deck.h"
#include <algorithm>
#include <ctime>
#include <random>

namespace system_p {

Deck Deck::createStandardDeck()
{
  Deck deck;
  for (int s = 0; s < 4; ++s) {
    for (int r = 2; r <= 14; ++r) { // BUG FIX #1: Ace = 14 (bukan 1), konsisten dengan
                                    // RoyalFlushChecker & StraightFlushChecker
      deck.cards.emplace_back(r, static_cast<Suit>(s));
    }
  }
  return deck;
}

void Deck::shuffle()
{
  static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
  std::shuffle(cards.begin(), cards.end(), g);
}

Hand Deck::draw(int count)
{
  Hand hand;
  for (int i = 0; i < count && !cards.empty(); ++i) {
    hand.push_back(cards.back());
    cards.pop_back();
  }
  return hand;
}

void Deck::addCard(const Card& card)
{
  // BUG FIX #3: Tambahkan kartu baru ke dalam deck
  cards.push_back(card);
}

Card Deck::drawCard() {
    if (cards.empty()) {
        return Card();
    }
    Card c = cards.back();
    cards.pop_back();
    return c;
}

} // namespace system_p
