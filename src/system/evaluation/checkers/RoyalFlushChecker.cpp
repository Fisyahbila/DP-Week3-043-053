#include "RoyalFlushChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType RoyalFlushChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Royal Flush..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::ROYAL_FLUSH;
    }

} // namespace system_p
