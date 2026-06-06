#ifndef MONEY_H
#define MONEY_H

namespace mechanic {

// Tracks player's money throughout the run
class Money {
public:
  explicit Money(int startAmount = 4) : amount(startAmount) {}

  int getAmount() const { return amount; }

  bool spend(int cost)
  {
    if (amount >= cost) {
      amount -= cost;
      return true;
    }
    return false;
  }

  void earn(int gained) { amount += gained; }

  bool canAfford(int cost) const { return amount >= cost; }

private:
  int amount;
};

} // namespace mechanic

#endif // MONEY_H