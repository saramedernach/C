#ifndef MYNOODLESHOP_H
#define MYNOODLESHOP_H

#include "NoodleShop.h"
#include "Objects.h"

#include <map>
#include <queue>
#include <algorithm>
#include <list>

using namespace std;

struct MyOrder: public Order {

  int mID;
  string mNoodle;
  int minute;

};

struct MyNoodle: public Noodle {

  string mName;
  int mBatchSize;
  int mCookTime;
  int mIngredientCost;
  int mServingPrice;

  queue<MyOrder> orders;

};

struct Pot {

  string noodle = "";
  int readyAt = 0;
  int staleAt = 0;
  int servings = 0;
  int cookTime = 0;
  int potID;
  bool dirty = false;

};

class MyNoodleShop: public NoodleShop {

  // Member Variables
  int mNpots;
  int mRent;
  int mCustomers;
  vector<Noodle> mNoodles;
  map<string, MyNoodle> noodleOrder;
  vector<Pot> pots;
  map<string, Pot> inUsePots;
  string onlyOption = "";

public:

  MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles);

  // Required Member Functions
  std::vector<Order> orders(int minute, std::vector<Order> orderlist);
  Action* action(int minute);

  // Other Member Functions
  bool Cook();
  bool ServeOrder(int minute);
  bool Clean(int minute);

};

#endif
