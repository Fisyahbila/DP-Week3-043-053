#pragma once
#include "../PokerHandChecker.h"

namespace system_p {

class FourOfAKindChecker : public PokerHandChecker {
public:
  PokerHandType check(const Hand& hand) override;
};

} // namespace system_p