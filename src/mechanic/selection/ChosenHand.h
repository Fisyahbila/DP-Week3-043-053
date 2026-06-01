#ifndef CHOSEN_HAND_H
#define CHOSEN_HAND_H

#include <vector>

namespace mechanic {

// Menyimpan indices kartu yang dipilih player dari hand-nya
class ChosenHand {
public:
  // Tambah index kartu yang dipilih
  void selectCard(int index);

  // Hapus index kartu dari pilihan
  void deselectCard(int index);

  // Reset semua pilihan
  void clear();

  // Ambil semua indices yang dipilih
  const std::vector<int>& getSelectedIndices() const;

  // Jumlah kartu yang dipilih
  int count() const;

private:
  std::vector<int> selectedIndices;
};

} // namespace mechanic

#endif // CHOSEN_HAND_H