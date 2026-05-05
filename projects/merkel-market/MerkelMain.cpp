#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>

MerkelMain::MerkelMain() {}

void MerkelMain::init() {
  int input;
  currentTime = orderBook.getEarliestTime();
  while (true) {
    printMenu();
    input = getUserOption();
    processUserOption(input);
  }
}

void MerkelMain::printMenu() {
  // 1 print help
  std::cout << "1: Print help" << std::endl;
  // 2 print exchange stats
  std::cout << "2: Print exchange stats" << std::endl;
  // 3 make an offer
  std::cout << "3: Make an ask" << std::endl;
  // 4 make a bid
  std::cout << "4: Make a bid" << std::endl;
  // 5 print wallet
  std::cout << "5: Print wallet" << std::endl;
  // 6 continue
  std::cout << "6: Continue" << std::endl;

  std::cout << "=======================" << std::endl;
  std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp() {
  std::cout << "Help - choose options from the menu" << std::endl;
  std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats() {
  for (std::string const &p : orderBook.getKnownProducts()) {
    std::cout << "Product: " << p << std::endl;
    std::vector<OrderBookEntry> entries =
        orderBook.getOrders(OrderBookType::ask, p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    std::cout << "Avg ask: " << OrderBook::getAvgPrice(entries) << std::endl;
  }
  // std::cout << "Order book contains " << orders.size() << std::endl;
  //
  // unsigned int bids = 0;
  // unsigned int asks = 0;
  //
  // for (OrderBookEntry &e : orders) {
  //   if (e.orderType == OrderBookType::ask) {
  //     asks++;
  //   }
  //   if (e.orderType == OrderBookType::bid) {
  //     bids++;
  //   }
  // }
  //
  // std::cout << "Order book asks: " << asks << " bids: " << bids << std::endl;
}

void MerkelMain::enterAsk() {
  std::cout << "Make an ask - enter the amount: product, price, amount, eg "
               "ETH/BTC,200,0.5"
            << std::endl;
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3) {
    std::cout << "Bad input! " << input << std::endl;
  } else {
    try {
      OrderBookEntry obe = CSVReader::stringsToOBE(
          tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
      orderBook.insertOrder(obe);
    } catch (const std::exception &e) {
      std::cout << "MerkelMain::enterAsk Bad input " << std::endl;
    }
  }
  std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid() {
  std::cout << "Make a bid - enter the amount." << std::endl;
}

void MerkelMain::printWallet() {
  std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeframe() {
  std::cout << "Continue." << std::endl;
  currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption() {
  int userOption;
  std::string line;

  std::cout << "Type in 1-6" << std::endl;
  std::getline(std::cin, line);

  try {
    userOption = std::stoi(line);
  } catch (const std::exception &e) {
    //
  }
  std::cout << "Your chose: " << userOption << std::endl;

  return userOption;
}

void MerkelMain::processUserOption(int userOption) {
  if (userOption < 1 || userOption > 6) {
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
  }
  if (userOption == 1) {
    printHelp();
  }
  if (userOption == 2) {
    printMarketStats();
  }
  if (userOption == 3) {
    enterAsk();
  }
  if (userOption == 4) {
    enterBid();
  }
  if (userOption == 5) {
    printWallet();
  }
  if (userOption == 6) {
    gotoNextTimeframe();
  }
}
