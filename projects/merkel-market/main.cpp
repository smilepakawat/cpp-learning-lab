#include "CSVReader.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"

int main() {
  MerkelMain app{};
  app.init();
  // CSVReader::readCSV("data/order_book.csv");
  return 0;
}
