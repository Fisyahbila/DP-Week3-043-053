#include "Money.h"
#include <iostream>

namespace mechanic {

Money::Money(int startAmount) : amount_(startAmount)
{
}

int Money::getAmount() const
{
  return amount_;
}

bool Money::spend(int cost)
{
  if (amount_ >= cost) {
    amount_ -= cost;
    std::cout << "[Money] Menghabiskan $" << cost << ". Sisa: $" << amount_ << std::endl;
    return true;
  }
  std::cout << "[Money] Gagal: saldo $" << amount_ << " tidak cukup untuk $" << cost << std::endl;
  return false;
}

void Money::earn(int gained)
{
  amount_ += gained;
  std::cout << "[Money] Mendapat $" << gained << ". Total: $" << amount_ << std::endl;
}

bool Money::canAfford(int cost) const
{
  return amount_ >= cost;
}

} // namespace mechanic