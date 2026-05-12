#include "StraightFlushChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType StraightFlushChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Straight Flush..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::STRAIGHT_FLUSH;
    }

} // namespace system_p
