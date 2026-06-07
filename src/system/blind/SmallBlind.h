#ifndef SMALL_BLIND_H
#define SMALL_BLIND_H

#include "BlindRule.h"

namespace system_p {

class SmallBlind : public BlindRule {
public:
  explicit SmallBlind(int ante);
  std::string getName() const override;
  int getTargetScore() const override;
  bool checkTarget(int score) override;

  // Skip reward: +1 BonusHand di blind berikutnya
  std::unique_ptr<mechanic::PendingCommand> createSkipRewardCommand(int& remainingPlays,
                                                                    Deck& deck,
                                                                    int& freeRerolls) const override;

private:
  int targetScore;
};

} // namespace system_p

#endif // SMALL_BLIND_H