#ifndef RUN_SESSION_SERVICE_H
#define RUN_SESSION_SERVICE_H

#include "../card/Deck.h"
#include "../card/HandState.h"
#include "../scoring/ScoringRule.h"
#include "../blind/BlindManager.h"
#include "RoundState.h"
#include "../../mechanic/reward/RewardManager.h"
#include "RunSessionState.h"

namespace system_p {

class RunSessionService {
public:
    RunSessionService();
    void runSession();

private:
    void drawInitialHand();
    void printCurrentState();
    int readPlayerActionRequest();
    bool canPerformAction(int action);
    void processPlayerAction(int action);
    void executePendingCommands(mechanic::CommandTiming timing);
    bool playBlind(int ante, int blindIndex);
    void printHand();

    RunSessionState sessionState;
    Deck deck;
    HandState handState;
    ScoringRule scoringRule;
    BlindManager blindManager;
    RoundState roundState;
    mechanic::RewardManager rewardManager;
    bool isGameOver;
};

} // namespace system_p

#endif // RUN_SESSION_SERVICE_H
