#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Objects.h"
#include "Actions.h"

#include <map>
#include <queue>
#include <vector>

class Validator {
  struct PotInfo {
    std::string  noodle;
    unsigned int ready_at;
    unsigned int stale_at;
    unsigned int servings;
  };

  struct OrderInfo {
    unsigned int id;
    std::string  noodle;
    unsigned int minute;
  };

  struct NoodleInfo {
    unsigned int cook_time;
    unsigned int batch_size;
    unsigned int ingredient_cost;
    unsigned int serving_price;

    unsigned int profit;
    unsigned int loss;

    std::queue<OrderInfo> orders;
  };

private:
  std::map<std::string, NoodleInfo> mNoodles;
  std::map<unsigned int, OrderInfo> mOrders;
  std::vector<PotInfo> mPots;

  unsigned int mCoGS;
  unsigned int mIncome;
  unsigned int mRent;
  unsigned int mMinute;

public:
  Validator(unsigned int npots, unsigned int rent, std::vector<Noodle> noodles);

  unsigned int cogs()   const;
  unsigned int income() const;
  unsigned int rent()   const;

  void orders(unsigned int minute, const std::vector<Order>& orders);
  void summarize() const;

  void validate(const Action*      action);
  void validate(const CookAction*  action);
  void validate(const CleanAction* action);
  void validate(const ServeAction* action);
  void validate(const NoAction*    action);
};

#endif
