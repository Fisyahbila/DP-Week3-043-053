#include "FiveOfAKindChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType FiveOfAKindChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Five of a Kind..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FIVE_OF_A_KIND;
    }

} // namespace system_p
