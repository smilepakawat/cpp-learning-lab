#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <vector>

class OrderBook {
public:
  OrderBook(std::string filename);
  std::vector<std::string> getKnownProducts();
  std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product,
                                        std::string timestamp);

private:
  std::vector<OrderBookEntry> orders;
};
