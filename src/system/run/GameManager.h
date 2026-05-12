#pragma once
#include "../card/Deck.h"
#include "../card/HandState.h"
#include "../scoring/ScoringRule.h"
#include "../blind/BlindRule.h"
#include "../../mechanic/reward/RewardRule.h"

namespace system_p {

class GameManager {
public:
    void runSession();

private:
    Deck        deck;
    HandState   handState;
    ScoringRule scoringRule;
    BlindRule   blindRule;
    mechanic::RewardRule rewardRule;
};

} // namespace system_p
