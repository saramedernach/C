#ifndef MYNOODLESHOP_H
#define MYNOODLESHOP_H

#include "NoodleShop.h"
#include "Objects.h"

#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class MyNoodleShop: public NoodleShop {

  // Member Variables
  int mNpots;
  int mRent;
  int mCustomers;
  vector<Noodle> mNoodles;
  map<string, queue<MyNoodle*>> noodleOrder;
  vector<Order> mOrderList;

public:

  MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles);

  // Required Member Functions
  std::vector<Order> orders(int minute, std::vector<Order> orderlist);
  Action* action(int minute);

  // Other Member Functions
};

class MyNoodle: public Noodle {

  string mName;
  int mBatchSize;
  int mCookTime;
  int mIngredientCost;
  int mServingPrice;

public:

  MyNoodle(string name, int batchSize, int cookTime, int ingredientCost, int servingPrice) {

    mName = name;
    mBatchSize = batchSize;
    mCookTime = cookTime;
    mIngredientCost = ingredientCost;
    mServingPrice = servingPrice;

  }

};

class MyOrder: public Order {

  int mID;
  string mNoodle;

public:

  MyOrder(int id, string noodle);

};

#endif
