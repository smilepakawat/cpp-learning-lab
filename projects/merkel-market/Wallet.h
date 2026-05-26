#include <map>
#include <string>

class Wallet {
public:
  Wallet();
  void insertCurrency(std::string type, double amount);
  bool containCurrency(std::string type, double amount);
  std::string toString();

private:
  std::map<std::string, double> currencies;
}
