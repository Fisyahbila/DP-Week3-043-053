#include "HighCardChecker.h"
#include <iostream>

namespace system_p {

    PokerHandType HighCardChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: High Card..." << std::endl;
        return PokerHandType::HIGH_CARD;
    }

} // namespace system_p
