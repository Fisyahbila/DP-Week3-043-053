#include "BossBlind.h"
#include <iostream>

namespace system_p {

BossBlind::BossBlind(int ante) {
    targetScore = 1600 * ante;
}

std::string BossBlind::getName() const {
    return "Boss Blind";
}

int BossBlind::getTargetScore() const {
    return targetScore;
}

bool BossBlind::checkTarget(int score) {
    std::cout << "[Boss Blind] Checking score: " << score << " / " << targetScore << std::endl;
    std::cout << "[Boss Blind] Active Modifier: None (Standard Boss)" << std::endl;
    return score >= targetScore;
}

} // namespace system_p
