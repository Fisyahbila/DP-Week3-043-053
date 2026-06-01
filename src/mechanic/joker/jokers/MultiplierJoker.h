#ifndef MULTIPLIER_JOKER_H
#define MULTIPLIER_JOKER_H

#include "../Joker.h"

namespace mechanic {
    class MultiplierJoker : public Joker {
    public:
        void apply(ScoreContext& ctx, const system_p::PlayedHandResult& result) override;
    };
}

#endif // MULTIPLIER_JOKER_H
