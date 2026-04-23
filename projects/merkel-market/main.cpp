#include "CSVReader.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
  // MerkelMain app{};
  // app.init();
  CSVReader::readCSV("data/order_book.csv");
  return 0;
}
