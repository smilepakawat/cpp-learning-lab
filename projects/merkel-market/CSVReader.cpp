#include "CSVReader.h"
#include <iostream>

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> CSVReader::readCsv(std::string csvFile) {
  std::vector<OrderBookEntry> entries;
  return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine,
                                             char separator) {
  std::vector<std::string> tokens;
  return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
  double price, amount;

  if (tokens.size() != 5) {
    std::cout << "Bad line " << std::endl;
    throw std::exception{};
  }

  try {
    price = std::stod(tokens[3]);
    amount = std::stod(tokens[4]);
  } catch (std::exception &e) {
    throw;
  }

  OrderBookEntry obe{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};

  return obe;
}
