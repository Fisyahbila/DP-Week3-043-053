#include "MultiplierJoker.h"
#include <iostream>

namespace mechanic {
    void MultiplierJoker::apply(ScoreContext& ctx, const system_p::PlayedHandResult& result) {
        ctx.mult += 4;
        std::cout << "[MultiplierJoker] +4 Mult diterapkan. Mult sekarang: " << ctx.mult << std::endl;
    }
}
