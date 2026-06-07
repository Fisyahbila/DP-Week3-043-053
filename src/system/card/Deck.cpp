#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>

namespace system_p {

Deck Deck::createStandardDeck() {
    Deck deck;
    for (int s = 0; s < 4; ++s) {
        for (int r = 1; r <= 13; ++r) {
            deck.cards.emplace_back(r, static_cast<Suit>(s));
        }
    }
    return deck;
}

void Deck::shuffle() {
    static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cards.begin(), cards.end(), g);
}

Hand Deck::draw(int count) {
    Hand hand;
    for (int i = 0; i < count && !cards.empty(); ++i) {
        hand.push_back(cards.back());
        cards.pop_back();
    }
    return hand;
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
