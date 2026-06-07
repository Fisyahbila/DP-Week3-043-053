#include "BlindManager.h"
#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "BossBlindState.h"
#include <functional>
#include <iostream>

namespace system_p {

BlindManager::BlindManager() : currentBlindState(nullptr), currentAnte(1) {}

BlindManager::~BlindManager() = default;

void BlindManager::selectBlind(int ante, int blindTypeIndex) {
    currentAnte = ante;
    static const std::function<std::shared_ptr<BlindState>()> factories[] = {
        []() { return std::make_shared<SmallBlindState>(); },
        []() { return std::make_shared<BigBlindState>(); },
        []() { return std::make_shared<BossBlindState>(); }
    };
    if (blindTypeIndex >= 0 && blindTypeIndex < 3) {
        currentBlindState = factories[blindTypeIndex]();
    } else {
        currentBlindState = factories[0]();
    }
}

BlindState* BlindManager::getCurrentBlind() const {
    return currentBlindState.get();
}

bool BlindManager::isTargetMet(int score) const {
    if (currentBlindState != nullptr) {
        int target = currentBlindState->getTargetScore(currentAnte);
        std::cout << "[" << currentBlindState->getName() << "] Checking score: " << score << " / " << target << std::endl;
        if (currentBlindState->getName() == "Boss Blind") {
            std::cout << "[Boss Blind] Active Modifier: None (Standard Boss)" << std::endl;
        }
        return score >= target;
    }
    return false;
}

int BlindManager::getCurrentTargetScore() const {
    if (currentBlindState != nullptr) {
        return currentBlindState->getTargetScore(currentAnte);
    }
    return 0;
}

std::string BlindManager::getCurrentBlindName() const {
    if (currentBlindState != nullptr) {
        return currentBlindState->getName();
    }
    return "None";
}

} // namespace system_p
