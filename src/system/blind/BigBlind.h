#ifndef BIG_BLIND_H
#define BIG_BLIND_H

#include "BlindRule.h"

namespace system_p {

class BigBlind : public BlindRule {
public:
  explicit BigBlind(int ante);
  std::string getName() const override;
  int getTargetScore() const override;
  bool checkTarget(int score) override;

  // Skip reward: Free Playing Card ditambahkan ke deck saat Start
  std::unique_ptr<mechanic::PendingCommand> createSkipRewardCommand(int& remainingPlays,
                                                                    Deck& deck,
                                                                    int& freeRerolls) const override;

private:
  int targetScore;
};

} // namespace system_p

#endif // BIG_BLIND_H