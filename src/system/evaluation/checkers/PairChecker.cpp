#include "PairChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType PairChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Pair..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::PAIR;
    }

} // namespace system_p
