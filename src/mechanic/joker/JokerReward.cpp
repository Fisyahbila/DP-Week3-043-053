#include "JokerReward.h"
#include <iostream>

namespace mechanic {

// JokerSlot
JokerSlot::JokerSlot(JokerManager& manager) : manager_(manager), usedSlots_(0)
{
}

bool JokerSlot::addJoker(JokerObserver* joker, const std::string& jokerName)
{
  if (isFull()) {
    std::cout << "[JokerSlot] Slot penuh (" << MAX_SLOTS << "/" << MAX_SLOTS
              << "). Tidak dapat menambah joker." << std::endl;
    return false;
  }

  manager_.attach(joker);
  ++usedSlots_;

  std::cout << "[JokerSlot] Joker '" << jokerName
            << "' berhasil masuk slot. Slot terpakai: " << usedSlots_ << "/" << MAX_SLOTS
            << std::endl;
  return true;
}

bool JokerSlot::removeJoker(JokerObserver* joker)
{
  if (usedSlots_ == 0) {
    return false;
  }

  manager_.detach(joker);
  --usedSlots_;

  std::cout << "[JokerSlot] Joker dilepas. Slot terpakai: " << usedSlots_ << "/" << MAX_SLOTS
            << std::endl;
  return true;
}

int JokerSlot::usedSlots() const
{
  return usedSlots_;
}
int JokerSlot::freeSlots() const
{
  return MAX_SLOTS - usedSlots_;
}
bool JokerSlot::isFull() const
{
  return usedSlots_ >= MAX_SLOTS;
}

// JokerReward
JokerReward::JokerReward(JokerSlot& slot) : slot_(slot)
{
}

bool JokerReward::grantJoker(JokerObserver* joker, const std::string& name)
{
  if (!canReceiveJoker()) {
    std::cout << "[JokerReward] Pemain tidak dapat menerima joker baru: slot penuh." << std::endl;
    // Joker tidak diambil alih — caller bertanggung jawab
    return false;
  }

  bool ok = slot_.addJoker(joker, name);
  if (ok) {
    std::cout << "[JokerReward] Joker '" << name
              << "' diberikan kepada pemain. Sisa slot: " << slot_.freeSlots() << std::endl;
  }
  return ok;
}

bool JokerReward::canReceiveJoker() const
{
  return !slot_.isFull();
}
int JokerReward::usedSlots() const
{
  return slot_.usedSlots();
}
int JokerReward::freeSlots() const
{
  return slot_.freeSlots();
}

} // namespace mechanic