#pragma once
#include "Card.h"

namespace system_p {

class HandState {
public:
    void addCards(const Hand& newCards);
    const Hand& getHand() const;
private:
    Hand currentHand;
};

} // namespace system_p
