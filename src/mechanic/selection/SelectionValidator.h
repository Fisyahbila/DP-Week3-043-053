#ifndef SELECTION_VALIDATOR_H
#define SELECTION_VALIDATOR_H

#include "ChosenHand.h"

namespace mechanic {

// Memvalidasi pilihan kartu dari player
class SelectionValidator {
public:
  static const int MAX_SELECTED_CARDS = 5;

  // Validasi lengkap: cek jumlah dan semua index valid
  // handSize = jumlah kartu di tangan player saat ini
  bool validate(const ChosenHand& chosenHand, int handSize) const;

  // Cek apakah jumlah kartu yang dipilih tidak melebihi MAX (5)
  bool isCountValid(const ChosenHand& chosenHand) const;

  // Cek apakah semua index valid (0 <= index < handSize)
  bool areIndicesValid(const ChosenHand& chosenHand, int handSize) const;
};

} // namespace mechanic

#endif // SELECTION_VALIDATOR_H