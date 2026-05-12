#include "FlushChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType FlushChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Flush..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FLUSH;
    }

} // namespace system_p
