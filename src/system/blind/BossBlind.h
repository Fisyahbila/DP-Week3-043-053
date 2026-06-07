#ifndef BOSS_BLIND_H
#define BOSS_BLIND_H

#include "BlindRule.h"

namespace system_p {

class BossBlind : public BlindRule {
public:
  explicit BossBlind(int ante);
  std::string getName() const override;
  int getTargetScore() const override;
  bool checkTarget(int score) override;

  // Skip reward: +1 FreeReroll di toko berikutnya
  std::unique_ptr<mechanic::PendingCommand> createSkipRewardCommand(int& remainingPlays,
                                                                    Deck& deck,
                                                                    int& freeRerolls) const override;

private:
  int targetScore;
};

} // namespace system_p

#endif // BOSS_BLIND_H