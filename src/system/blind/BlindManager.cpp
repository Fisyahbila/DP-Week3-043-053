#include "BlindManager.h"
#include "SmallBlind.h"
#include "BigBlind.h"
#include "BossBlind.h"

namespace system_p {

BlindManager::BlindManager() : currentBlind(nullptr) {}

BlindManager::~BlindManager() = default;

void BlindManager::selectBlind(int ante, int blindTypeIndex) {
    if (blindTypeIndex == 0) {
        currentBlind = std::make_unique<SmallBlind>(ante);
    } else if (blindTypeIndex == 1) {
        currentBlind = std::make_unique<BigBlind>(ante);
    } else if (blindTypeIndex == 2) {
        currentBlind = std::make_unique<BossBlind>(ante);
    } else {
        // Default to Small Blind if index is out of bounds
        currentBlind = std::make_unique<SmallBlind>(ante);
    }
}

BlindRule* BlindManager::getCurrentBlind() const {
    return currentBlind.get();
}

bool BlindManager::isTargetMet(int score) const {
    if (currentBlind != nullptr) {
        return currentBlind->checkTarget(score);
    }
    return false;
}

int BlindManager::getCurrentTargetScore() const {
    if (currentBlind != nullptr) {
        return currentBlind->getTargetScore();
    }
    return 0;
}

std::string BlindManager::getCurrentBlindName() const {
    if (currentBlind != nullptr) {
        return currentBlind->getName();
    }
    return "None";
}

} // namespace system_p
