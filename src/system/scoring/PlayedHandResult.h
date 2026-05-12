#ifndef PLAYED_HAND_RESULT_H
#define PLAYED_HAND_RESULT_H

#include "../evaluation/PokerHandType.h"

namespace system_p {
    class PlayedHandResult {
    public:
        const int baseChips;
        const int baseMult;
        const PokerHandType handType;

        PlayedHandResult(int chips, int mult, PokerHandType type)
            : baseChips(chips), baseMult(mult), handType(type) {}
    };
}

#endif // PLAYED_HAND_RESULT_H
