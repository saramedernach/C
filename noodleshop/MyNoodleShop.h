#ifndef MYNOODLESHOP_H
#define MYNOODLESHOP_H

#include "NoodleShop.h"

class MyNoodleShop: public NoodleShop {
  // Member Variables
public:
  // Constructor
  // Destructor?

  // Required Member Functions
  std::vector<Order> orders(unsigned int minute, std::vector<Order> orderlist);
  Action* action(int minute);

  // Other Member Functions
};

#endif
