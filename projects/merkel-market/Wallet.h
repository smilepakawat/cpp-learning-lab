#pragma once

#include "OrderBookEntry.h"
#include <map>
#include <string>

class Wallet {
public:
  Wallet();
  void insertCurrency(std::string type, double amount);
  bool removeCurrency(std::string type, double amount);
  bool containsCurrency(std::string type, double amount);
  bool canFulfillOrder(OrderBookEntry order);
  std::string toString();

private:
  std::map<std::string, double> currencies;
};
