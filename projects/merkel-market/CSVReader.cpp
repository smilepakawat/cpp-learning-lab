#include "CSVReader.h"

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> readCsv(std::string csvFile) {
  std::vector<OrderBookEntry> entries;
  return entries;
}

std::vector<std::string> tokenise(std::string csvLine, char separator) {
  std::vector<std::string> tokens;
  return tokens;
}

OrderBookEntry stringsToOBE(std::vector<std::string> strings) {
  OrderBookEntry obe{1, 1, "", "", OrderBookType::bid};
  return obe;
}
