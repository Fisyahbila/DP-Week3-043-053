#include "ChipBonusJoker.h"
#include <iostream>

namespace mechanic {
    void ChipBonusJoker::apply(ScoreContext& ctx, const system_p::PlayedHandResult& result) {
        ctx.chips += 50;
        std::cout << "[ChipBonusJoker] +50 Chips diterapkan. Chips sekarang: " << ctx.chips << std::endl;
    }
}
