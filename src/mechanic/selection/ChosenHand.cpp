#include "ChosenHand.h"
#include <algorithm>
#include <iostream>

namespace mechanic {

void ChosenHand::selectCard(int index)
{
  // Hindari duplicate index
  auto it = std::find(selectedIndices.begin(), selectedIndices.end(), index);
  if (it == selectedIndices.end()) {
    selectedIndices.push_back(index);
    std::cout << "[ChosenHand] Kartu index " << index
              << " dipilih. Total dipilih: " << selectedIndices.size() << std::endl;
  }
}

void ChosenHand::deselectCard(int index)
{
  auto it = std::find(selectedIndices.begin(), selectedIndices.end(), index);
  if (it != selectedIndices.end()) {
    selectedIndices.erase(it);
    std::cout << "[ChosenHand] Kartu index " << index
              << " dideselect. Total dipilih: " << selectedIndices.size() << std::endl;
  }
}

void ChosenHand::clear()
{
  selectedIndices.clear();
  std::cout << "[ChosenHand] Semua pilihan dihapus." << std::endl;
}

const std::vector<int>& ChosenHand::getSelectedIndices() const
{
  return selectedIndices;
}

int ChosenHand::count() const
{
  return static_cast<int>(selectedIndices.size());
}

} // namespace mechanic