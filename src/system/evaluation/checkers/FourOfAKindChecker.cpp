#include "FourOfAKindChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType FourOfAKindChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Four of a Kind..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FOUR_OF_A_KIND;
    }

} // namespace system_p
