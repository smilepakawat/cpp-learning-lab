#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"

MerkelMain::MerkelMain() {}

void MerkelMain::init() {
  loadOrderBook();
  int input;
  while(true) {
    printMenu();
    input = getUserOption();
    processUserOption(input);
  }
}

void MerkelMain::loadOrderBook() {
  orders.push_back(
      OrderBookEntry{
        1000,
        0.02,
        "2020/03/17 17:01:24.884492",
        "BTC/USDT",
        OrderBookType::bid
      }
  );
}

void MerkelMain::printMenu() {
  // 1 print help
  std::cout << "1: Print help" << std::endl;
  // 2 print exchange stats
  std::cout << "2: Print exchange stats" << std::endl;
  // 3 make an offer
  std::cout << "3: Place an ask"<< std::endl;
  // 4 make a bid
  std::cout << "4: Place a bid" << std::endl;
  // 5 print wallet
  std::cout << "5: Print wallet" << std::endl;
  // 6 continue
  std::cout << "6: Continue" << std::endl;

  std::cout << "=======================" << std::endl;
}

void MerkelMain::printHelp() {
  std::cout << "Help - choose options from the menu" << std::endl;
  std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats() {
  std::cout << "Order book contains " << orders.size() << std::endl;
}

void MerkelMain::enterOffer() {
  std::cout << "Place an ask - enter the amount." << std::endl;
}

void MerkelMain::enterBid() {
  std::cout << "Place a bid - enter the amount." << std::endl;
}

void MerkelMain::printWallet() {
  std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeframe() {
  std::cout << "Continue." << std::endl;
}

int MerkelMain::getUserOption() {
  int userOption;
  std::cout << "Type in 1-6" << std::endl;
  std::cin >> userOption;
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
    enterOffer();
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

