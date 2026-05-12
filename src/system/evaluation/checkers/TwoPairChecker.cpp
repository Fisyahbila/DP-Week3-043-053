#include "TwoPairChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType TwoPairChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Two Pair..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::TWO_PAIR;
    }

} // namespace system_p
