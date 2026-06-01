#ifndef CHIP_BONUS_JOKER_H
#define CHIP_BONUS_JOKER_H

#include "../Joker.h"

namespace mechanic {

class ChipBonusJoker : public JokerObserver {
public:
  void onNotify(ScoreContext& ctx, const system_p::PlayedHandResult& result) override;
};

} // namespace mechanic

#endif // CHIP_BONUS_JOKER_H