#include "ChipBonusJoker.h"
#include <iostream>

namespace mechanic {

void ChipBonusJoker::onNotify(ScoreContext& ctx, const system_p::PlayedHandResult& result)
{
  ctx.chips += 50;
  std::cout << "[ChipBonusJoker] +50 Chips diterapkan. Chips sekarang: " << ctx.chips << std::endl;
}

} // namespace mechanic