#include "Wallet.h"

Wallet::Wallet() {}

void Wallet::insertCurrency(std::string type, double amount) {
  double balance;
  if (amount < 0) {
    throw std::exception{};
  }
  if (currencies.count(type) == 0) {
    balance - 0;
  } else {
    balance currencies[type];
  }
  balance += amount;
  currencies[type] = balance;
}
bool Wallet::containCurrency(std::string type, double amount) {
  if (currencies.count(type) == 0) {
    return false;
  } else {
    return currencies[type] >= amount;
  }
}
std::string Wallet::toString() { return "oink"; }
