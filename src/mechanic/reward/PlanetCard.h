#ifndef PLANET_CARD_H
#define PLANET_CARD_H

#include "../../system/evaluation/PokerHandType.h"
#include <string>

namespace mechanic {

// Represents a Planet Card item available in the shop.
// Each card targets one PokerHandType for upgrading.
class PlanetCard {
public:
  PlanetCard(const std::string& name, system_p::PokerHandType targets, int cost = 3)
    : name_(name)
    , targets_(targets)
    , cost_(cost)
  {
  }

  const std::string& getName() const { return name_; }
  system_p::PokerHandType getTargetHand() const { return targets_; }
  int getCost() const { return cost_; }

private:
  std::string name_;
  system_p::PokerHandType targets_;
  int cost_;
};

} // namespace mechanic

#endif // PLANET_CARD_H