#include "OrderBook.h"
#include "CSVReader.h"
#include <map>

OrderBook::OrderBook(std::string filename) {
  orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
  std::vector<std::string> products;
  std::map<std::string, bool> prodMap;

  for (OrderBookEntry &e : orders) {
    prodMap[e.product] = true;
  }

  for (auto const &e : prodMap) {
    products.push_back(e.first);
  }

  return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp) {
  std::vector<OrderBookEntry> ordersSub;

  for (OrderBookEntry &e : orders) {
    if (e.orderType == type && e.product == product &&
        e.timestamp == timestamp) {
      ordersSub.push_back(e);
    }
  }

  return ordersSub;
}
