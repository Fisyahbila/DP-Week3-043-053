#pragma once
#include <vector>

namespace system_p {

enum class Suit { HEART, DIAMOND, CLUB, SPADE };

class Card {
public:
    int rank;
    Suit suit;
    Card(int r, Suit s) : rank(r), suit(s) {}
};

using Hand = std::vector<Card>;

} // namespace system_p
