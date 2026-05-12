#ifndef POKER_HAND_TYPE_H
#define POKER_HAND_TYPE_H

namespace system_p {
    enum class PokerHandType {
        ROYAL_FLUSH,
        STRAIGHT_FLUSH,
        FLUSH_FIVE,
        FIVE_OF_A_KIND,
        FOUR_OF_A_KIND,
        FLUSH_HOUSE,
        FULL_HOUSE,
        FLUSH,
        STRAIGHT,
        THREE_OF_A_KIND,
        TWO_PAIR,
        PAIR,
        HIGH_CARD,
        NONE
    };
}

#endif // POKER_HAND_TYPE_H
