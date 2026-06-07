#ifndef MONEY_H
#define MONEY_H

namespace mechanic {

// Mengelola mata uang koin (Money) pemain secara modular.
// Menyediakan operasi earn, spend, dan canAfford.
class Money {
public:
  explicit Money(int startAmount = 4);

  int getAmount() const;
  bool canAfford(int cost) const;

  // Kurangi saldo; return false jika tidak cukup
  bool spend(int cost);

  // Tambah saldo (reward setelah blind)
  void earn(int gained);

private:
  int amount_;
};

} // namespace mechanic

#endif // MONEY_H