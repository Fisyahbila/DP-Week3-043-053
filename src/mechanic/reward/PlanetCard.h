#ifndef PLANET_CARD_H
#define PLANET_CARD_H

#include "../../system/evaluation/PokerHandType.h"
#include "../../system/scoring/HandScoreTable.h"
#include <string>

namespace mechanic {

// HandModifier: antarmuka modifier untuk upgrade hand
class HandModifier {
public:
  virtual ~HandModifier() = default;

  // Terapkan modifikasi ke HandScoreTable untuk hand tertentu
  virtual void apply(system_p::HandScoreTable& table, system_p::PokerHandType hand) const = 0;

  virtual const char* modifierName() const = 0;
};

// StandardLevelUpModifier
// Modifier default: naik 1 level via upgradeHand()
class StandardLevelUpModifier : public HandModifier {
public:
  void apply(system_p::HandScoreTable& table, system_p::PokerHandType hand) const override
  {
    table.upgradeHand(hand);
  }

  const char* modifierName() const override { return "StandardLevelUp"; }
};

// PlanetCard
// Mewakili item Planet Card di toko.
// Menggunakan arsitektur modifier sehingga perilaku upgrade
// dapat diganti/diperluas tanpa mengubah kelas ini.
class PlanetCard {
public:
  // Constructor dengan modifier eksternal (ownership berpindah ke PlanetCard)
  PlanetCard(const std::string& name,
             system_p::PokerHandType targets,
             int cost,
             HandModifier* modifier);

  // Constructor convenience — menggunakan StandardLevelUpModifier
  PlanetCard(const std::string& name, system_p::PokerHandType targets, int cost = 3);

  ~PlanetCard();

  // Terapkan efek kartu ke HandScoreTable
  void applyTo(system_p::HandScoreTable& table) const;

  const std::string& getName() const;
  system_p::PokerHandType getTargetHand() const;
  int getCost() const;
  const char* getModifierName() const;

private:
  std::string name_;
  system_p::PokerHandType targets_;
  int cost_;
  HandModifier* modifier_; // owned
};

} // namespace mechanic

#endif // PLANET_CARD_H