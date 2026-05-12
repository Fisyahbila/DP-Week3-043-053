#include "StraightChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType StraightChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Straight..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::STRAIGHT;
    }

} // namespace system_p
