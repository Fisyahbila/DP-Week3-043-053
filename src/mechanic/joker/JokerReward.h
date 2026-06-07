#ifndef JOKER_REWARD_H
#define JOKER_REWARD_H

#include "../joker/Joker.h"
#include "../joker/JokerManager.h"
#include <string>

namespace mechanic {

// JokerSlot
// Mengelola slot Joker aktif milik pemain.
// Balatro membatasi maksimum 5 joker aktif.
class JokerSlot {
public:
  static constexpr int MAX_SLOTS = 5;

  explicit JokerSlot(JokerManager& manager);

  // Coba masukkan joker baru ke slot aktif.
  // Return true jika berhasil, false jika slot penuh.
  bool addJoker(JokerObserver* joker, const std::string& jokerName);

  // Lepas joker dari slot (berdasarkan pointer).
  bool removeJoker(JokerObserver* joker);

  int usedSlots() const;
  int freeSlots() const;
  bool isFull() const;

private:
  JokerManager& manager_;
  int usedSlots_;
};

// JokerReward
// Menangani pemberian Joker baru kepada pemain
// sebagai hadiah (reward) setelah blind selesai
// atau sebagai item di toko.
//
// Pola: memvalidasi ketersediaan slot, kemudian
// memanggil JokerSlot::addJoker() dan men-attach
// joker ke JokerManager.
class JokerReward {
public:
  explicit JokerReward(JokerSlot& slot);

  // Berikan joker ke pemain.
  // joker   : pointer ke Joker konkret (ownership berpindah ke JokerManager)
  // name    : nama tampilan untuk logging
  // Return true jika joker berhasil ditambahkan ke slot aktif.
  bool grantJoker(JokerObserver* joker, const std::string& name);

  // Cek apakah pemain masih bisa menerima joker baru
  bool canReceiveJoker() const;

  int usedSlots() const;
  int freeSlots() const;

private:
  JokerSlot& slot_;
};

} // namespace mechanic

#endif // JOKER_REWARD_H