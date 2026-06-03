#pragma once
#include "Card.h"
#include <vector>

namespace system_p {

class HandState {
public:
    void addCards(const Hand& newCards);
    void removeCards(const std::vector<int>& indices);
    void clear();
    const Hand& getHand() const;
private:
    Hand currentHand;
};

} // namespace system_p
