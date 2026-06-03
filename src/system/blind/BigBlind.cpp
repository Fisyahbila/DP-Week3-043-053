#include "BigBlind.h"
#include <iostream>

namespace system_p {

BigBlind::BigBlind(int ante) {
    targetScore = 800 * ante;
}

std::string BigBlind::getName() const {
    return "Big Blind";
}

int BigBlind::getTargetScore() const {
    return targetScore;
}

bool BigBlind::checkTarget(int score) {
    std::cout << "[Big Blind] Checking score: " << score << " / " << targetScore << std::endl;
    return score >= targetScore;
}

} // namespace system_p
