#pragma once
#include "../PokerHandChecker.h"

namespace system_p {

    class FlushChecker : public PokerHandChecker {
    public:
        PokerHandType check(const Hand& hand) override;
    };

} // namespace system_p
