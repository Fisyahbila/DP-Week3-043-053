#include "PlanetCard.h"
#include <iostream>

namespace mechanic {

// Constructor dengan modifier eksplisit
PlanetCard::PlanetCard(const std::string& name,
                       system_p::PokerHandType targets,
                       int cost,
                       HandModifier* modifier)
  : name_(name)
  , targets_(targets)
  , cost_(cost)
  , modifier_(modifier)
{
}

// Constructor convenience (StandardLevelUpModifier)
PlanetCard::PlanetCard(const std::string& name, system_p::PokerHandType targets, int cost)
  : name_(name)
  , targets_(targets)
  , cost_(cost)
  , modifier_(new StandardLevelUpModifier())
{
}

PlanetCard::~PlanetCard()
{
  delete modifier_;
}

// Terapkan efek kartu ke tabel
void PlanetCard::applyTo(system_p::HandScoreTable& table) const
{
  std::cout << "[PlanetCard] Menerapkan " << name_ << " (modifier: " << modifier_->modifierName()
            << ") ke " << table.getHandName(targets_) << std::endl;
  modifier_->apply(table, targets_);
}

const std::string& PlanetCard::getName() const
{
  return name_;
}
system_p::PokerHandType PlanetCard::getTargetHand() const
{
  return targets_;
}
int PlanetCard::getCost() const
{
  return cost_;
}
const char* PlanetCard::getModifierName() const
{
  return modifier_->modifierName();
}

} // namespace mechanic