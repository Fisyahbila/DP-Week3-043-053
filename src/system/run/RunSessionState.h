#ifndef RUN_SESSION_STATE_H
#define RUN_SESSION_STATE_H

#include <vector>
#include <string>
#include <memory>
#include "../blind/BlindState.h"
#include "../../mechanic/reward/RewardCommand.h"

namespace system_p {

struct RunPersistentState {
    int ante = 1;
    int money = 4;
    std::vector<std::string> jokers;
    std::vector<mechanic::PendingCommand> pendingCommands;
    std::shared_ptr<BlindState> currentBlind;
    int freeRerolls = 0;
    int bonusHands = 0;
};

struct BlindRuntimeState {
    int blindScore = 0;
    int remainingHands = 4;
    int remainingDiscards = 4;
};

struct RunSessionState {
    RunPersistentState persistentState;
    BlindRuntimeState runtimeState;
};

} // namespace system_p

#endif // RUN_SESSION_STATE_H
