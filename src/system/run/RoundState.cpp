#include "RoundState.h"

namespace system_p {

RoundState::RoundState(int maxH, int maxD)
    : maxHands(maxH), maxDiscards(maxD), handsRemaining(maxH), discardsRemaining(maxD), currentScore(0) {}

int RoundState::getHandsRemaining() const {
    return handsRemaining;
}

int RoundState::getDiscardsRemaining() const {
    return discardsRemaining;
}

int RoundState::getCurrentScore() const {
    return currentScore;
}

void RoundState::addScore(int score) {
    currentScore += score;
}

bool RoundState::useHand() {
    if (handsRemaining > 0) {
        handsRemaining--;
        return true;
    }
    return false;
}

bool RoundState::useDiscard() {
    if (discardsRemaining > 0) {
        discardsRemaining--;
        return true;
    }
    return false;
}

void RoundState::reset() {
    handsRemaining = maxHands;
    discardsRemaining = maxDiscards;
    currentScore = 0;
}

} // namespace system_p
