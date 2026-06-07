#ifndef BLIND_STATE_H
#define BLIND_STATE_H

#include <string>
#include <memory>

namespace mechanic {
class PendingCommand;
}

namespace system_p {

class Deck;

class BlindState {
public:
    virtual ~BlindState() = default;
    virtual std::string getName() const = 0;
    virtual int getTargetScore(int ante) const = 0;
    virtual int getRewardMoney() const = 0;
    virtual std::unique_ptr<mechanic::PendingCommand> createSkipRewardCommand(int& remainingPlays, Deck& deck, int& freeRerolls) const = 0;
    virtual std::shared_ptr<BlindState> extState(int& ante) = 0;
    virtual std::shared_ptr<BlindState> nextState(int& ante) { return extState(ante); }
};

} // namespace system_p

#endif // BLIND_STATE_H
