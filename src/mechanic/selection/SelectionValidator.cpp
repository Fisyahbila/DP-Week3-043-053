#include "SelectionValidator.h"
#include <iostream>

namespace mechanic {

bool SelectionValidator::validate(const ChosenHand& chosenHand, int handSize) const
{
  if (!isCountValid(chosenHand)) {
    std::cout << "[SelectionValidator] INVALID: Terlalu banyak kartu dipilih ("
              << chosenHand.count() << " > " << MAX_SELECTED_CARDS << ")" << std::endl;
    return false;
  }
  if (!areIndicesValid(chosenHand, handSize)) {
    std::cout << "[SelectionValidator] INVALID: Ada index yang tidak valid." << std::endl;
    return false;
  }
  std::cout << "[SelectionValidator] Pilihan valid: " << chosenHand.count() << " kartu dipilih."
            << std::endl;
  return true;
}

bool SelectionValidator::isCountValid(const ChosenHand& chosenHand) const
{
  return chosenHand.count() >= 1 && chosenHand.count() <= MAX_SELECTED_CARDS;
}

bool SelectionValidator::areIndicesValid(const ChosenHand& chosenHand, int handSize) const
{
  for (int index : chosenHand.getSelectedIndices()) {
    if (index < 0 || index >= handSize) {
      std::cout << "[SelectionValidator] Index " << index << " tidak valid (hand size: " << handSize
                << ")" << std::endl;
      return false;
    }
  }
  return true;
}

} // namespace mechanic