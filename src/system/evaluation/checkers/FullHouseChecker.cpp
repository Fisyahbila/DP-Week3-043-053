#include "FullHouseChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType FullHouseChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Full House..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FULL_HOUSE;
    }

} // namespace system_p
