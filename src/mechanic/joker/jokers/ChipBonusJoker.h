#ifndef CHIP_BONUS_JOKER_H
#define CHIP_BONUS_JOKER_H

#include "../Joker.h"

namespace mechanic {
    class ChipBonusJoker : public Joker {
    public:
        void apply(ScoreContext& ctx, const system_p::PlayedHandResult& result) override;
    };
}

#endif // CHIP_BONUS_JOKER_H
