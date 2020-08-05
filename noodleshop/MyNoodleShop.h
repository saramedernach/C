#ifndef MYNOODLESHOP_H
#define MYNOODLESHOP_H

#include "NoodleShop.h"

using namespace std;

class MyNoodleShop: public NoodleShop {

  // Member Variables
  int mNpots;
  int mRent;
  int mCustomers;
  vector<Noodle> mNoodles;

public:

  MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles);

  // Required Member Functions
  std::vector<Order> orders(int minute, std::vector<Order> orderlist);
  Action* action(int minute);

  // Other Member Functions
};

#endif
