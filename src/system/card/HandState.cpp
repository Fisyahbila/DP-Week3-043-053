#include "HandState.h"
#include <algorithm>

namespace system_p {

void HandState::addCards(const Hand& newCards) {
    currentHand.insert(currentHand.end(), newCards.begin(), newCards.end());
}

void HandState::removeCards(const std::vector<int>& indices) {
    std::vector<int> sortedIndices = indices;
    std::sort(sortedIndices.rbegin(), sortedIndices.rend());
    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < static_cast<int>(currentHand.size())) {
            currentHand.erase(currentHand.begin() + idx);
        }
    }
}

void HandState::clear() {
    currentHand.clear();
}

const Hand& HandState::getHand() const {
    return currentHand;
}

} // namespace system_p
