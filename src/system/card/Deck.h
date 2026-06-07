#pragma once
#include "Card.h"
#include <vector>

namespace system_p {

class Deck {
public:
    static Deck createStandardDeck();
    void shuffle();
    Hand draw(int count);
    Card drawCard();
private:
    std::vector<Card> cards;
};

} // namespace system_p
