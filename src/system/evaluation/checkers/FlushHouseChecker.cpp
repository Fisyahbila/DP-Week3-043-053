#include "FlushHouseChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType FlushHouseChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Flush House..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FLUSH_HOUSE;
    }

} // namespace system_p
