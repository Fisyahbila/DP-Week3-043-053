#include "ThreeOfAKindChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType ThreeOfAKindChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Three of a Kind..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::THREE_OF_A_KIND;
    }

} // namespace system_p
