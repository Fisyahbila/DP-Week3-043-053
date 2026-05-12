#include "FlushFiveChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType FlushFiveChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Flush Five..." << std::endl;
        // Logic will be implemented by System Programmer
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FLUSH_FIVE;
    }

} // namespace system_p
