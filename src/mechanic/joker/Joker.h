#ifndef JOKER_H
#define JOKER_H

#include "ScoreContext.h"
#include "../../system/scoring/PlayedHandResult.h"

namespace mechanic {
    class Joker {
    public:
        virtual void apply(ScoreContext& ctx, const system_p::PlayedHandResult& result) = 0;
        virtual ~Joker() = default;
    };
}

#endif // JOKER_H
