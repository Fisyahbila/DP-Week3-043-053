#ifndef BLIND_RULE_H
#define BLIND_RULE_H

#include <memory>
#include <string>

namespace mechanic {
class PendingCommand;
}

namespace system_p {

class Deck;

class BlindRule {
public:
  virtual ~BlindRule() = default;
  virtual std::string getName() const = 0;
  virtual int getTargetScore() const = 0;
  virtual bool checkTarget(int score) = 0;

  // Membuat PendingCommand hadiah ketika player meng-skip blind ini
  virtual std::unique_ptr<mechanic::PendingCommand>
  createSkipRewardCommand(int& remainingPlays, Deck& deck, int& freeRerolls) const = 0;
};

} // namespace system_p

#endif // BLIND_RULE_H