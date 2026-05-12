#include "HandState.h"

namespace system_p {

void HandState::addCards(const Hand& newCards) {
    currentHand.insert(currentHand.end(), newCards.begin(), newCards.end());
}

const Hand& HandState::getHand() const {
    return currentHand;
}

} // namespace system_p
