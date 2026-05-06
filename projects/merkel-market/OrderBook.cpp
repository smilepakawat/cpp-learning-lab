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

std::string OrderBook::getEarliestTime() { return orders[0].timestamp; }

std::string OrderBook::getNextTime(std::string timestamp) {
  std::string nextTimestamp = "";

  for (OrderBookEntry &e : orders) {
    if (e.timestamp > timestamp) {
      nextTimestamp = e.timestamp;
      break;
    }
  }

  if (nextTimestamp == "") {
    nextTimestamp = orders[0].timestamp;
  }

  return nextTimestamp;
}

void OrderBook::insertOrder(OrderBookEntry &order) {
  orders.push_back(order);
  std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids() {
  // TODO: Implement it
  // asks = orderbook.asks in this timeframe
  // bids = orderbook.bids in this timeframe
  // sales = []
  // sort asks lowest first
  // sort bids highest first
  // for ask in asks:
  //    for bid in bids:
  //        if bid.price >= ask.price # we have a match
  //            sale = new orderbookentry()
  //            sale.price = ask.price
  //            if bid.amount == ask.amount: # bid completely clears ask
  //                sale.amount = ask.amount
  //                sales.append(sale)
  //                bid.amount = 0 # make sure the bid is not processed again
  //                # can do no more with this ask
  //                # go onto the next ask
  //                break
  //            if bid.amount > ask.amount: # ask is completely gone slice the
  //            bid
  //                sale.amount = ask.amount
  //                sales.append(sale)
  //                # we adjust the bid in place
  //                # so it can be used to process the next ask
  //                bid.amount = bid.amount - ask.amount
  //                # ask is completely gone, so go to next ask
  //                break
  //            if bid.amount < ask.amount # bid is completely gone, slice the
  //            ask
  //                sale.amount = bid.amount
  //                sales.append(sale)
  //                # update the ask
  //                # and allow further bids to process the remaining amount
  //                ask.amount = ask.amount - bid.amount
  //                bid.amount = 0 # make sure the bid is not processed again
  //                # some ask remains so go to the next bid
  //                continue
  // return sales
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders) {
  double max = orders[0].price;

  for (OrderBookEntry &e : orders) {
    if (e.price > max) {
      max = e.price;
    }
  }

  return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders) {
  double min = orders[0].price;

  for (OrderBookEntry &e : orders) {
    if (e.price < min) {
      min = e.price;
    }
  }

  return min;
}

double OrderBook::getAvgPrice(std::vector<OrderBookEntry> &orders) {
  long double sum = 0;

  for (OrderBookEntry &e : orders) {
    sum += e.price;
  }

  return sum / orders.size();
}
