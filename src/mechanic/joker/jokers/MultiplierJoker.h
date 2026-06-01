#ifndef MULTIPLIER_JOKER_H
#define MULTIPLIER_JOKER_H

#include "../Joker.h"

namespace mechanic {

class MultiplierJoker : public JokerObserver {
public:
  void onNotify(ScoreContext& ctx, const system_p::PlayedHandResult& result) override;
};

} // namespace mechanic

#endif // MULTIPLIER_JOKER_H