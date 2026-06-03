#include "SmallBlind.h"
#include <iostream>

namespace system_p {

SmallBlind::SmallBlind(int ante) {
    targetScore = 300 * ante;
}

std::string SmallBlind::getName() const {
    return "Small Blind";
}

int SmallBlind::getTargetScore() const {
    return targetScore;
}

bool SmallBlind::checkTarget(int score) {
    std::cout << "[Small Blind] Checking score: " << score << " / " << targetScore << std::endl;
    return score >= targetScore;
}

} // namespace system_p
