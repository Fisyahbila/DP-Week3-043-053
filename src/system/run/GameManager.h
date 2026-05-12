#pragma once
#include "../card/HandGenerator.h"
#include "../card/HandPlayer.h"
#include "../scoring/ScoringRule.h"
#include "../blind/BlindRule.h"
#include "../../mechanic/reward/RewardRule.h"

class GameManager {
public:
    void runSession();

private:
    HandGenerator handGenerator;
    HandPlayer    handPlayer;
    ScoringRule   scoringRule;
    BlindRule     blindRule;
    mechanic::RewardRule rewardRule;
};