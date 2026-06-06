#ifndef PLANET_CARD_FACTORY_H
#define PLANET_CARD_FACTORY_H

#include "../../system/evaluation/PokerHandType.h"
#include "PlanetCard.h"

namespace mechanic {

// Factory untuk membuat PlanetCard berdasarkan index pilihan player.
// Mengikuti Balatro lore: tiap planet = satu hand type.
class PlanetCardFactory {
public:
  // Membuat PlanetCard berdasarkan menu index (1-7)
  // Returns nullptr jika index tidak valid
  static PlanetCard* create(int menuIndex)
  {
    switch (menuIndex) {
      case 1:  return new PlanetCard("Mercury", system_p::PokerHandType::HIGH_CARD);
      case 2:  return new PlanetCard("Venus", system_p::PokerHandType::PAIR);
      case 3:  return new PlanetCard("Earth", system_p::PokerHandType::TWO_PAIR);
      case 4:  return new PlanetCard("Mars", system_p::PokerHandType::THREE_OF_A_KIND);
      case 5:  return new PlanetCard("Jupiter", system_p::PokerHandType::STRAIGHT);
      case 6:  return new PlanetCard("Saturn", system_p::PokerHandType::FLUSH);
      case 7:  return new PlanetCard("Uranus", system_p::PokerHandType::FULL_HOUSE);
      default: return nullptr;
    }
  }

  // Overload: buat langsung dari PokerHandType
  static PlanetCard* create(system_p::PokerHandType type, int cost = 3)
  {
    switch (type) {
      case system_p::PokerHandType::HIGH_CARD:       return new PlanetCard("Mercury", type, cost);
      case system_p::PokerHandType::PAIR:            return new PlanetCard("Venus", type, cost);
      case system_p::PokerHandType::TWO_PAIR:        return new PlanetCard("Earth", type, cost);
      case system_p::PokerHandType::THREE_OF_A_KIND: return new PlanetCard("Mars", type, cost);
      case system_p::PokerHandType::STRAIGHT:        return new PlanetCard("Jupiter", type, cost);
      case system_p::PokerHandType::FLUSH:           return new PlanetCard("Saturn", type, cost);
      case system_p::PokerHandType::FULL_HOUSE:      return new PlanetCard("Uranus", type, cost);
      default:                                       return nullptr;
    }
  }
};

} // namespace mechanic

#endif // PLANET_CARD_FACTORY_H