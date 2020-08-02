#ifndef ORDER_H
#define ORDER_H

#include <string>

// This class contains information
// about a single type of noodle.
struct Noodle {
  // The name of the noodle.
  std::string name;

  // The price of the ingredients needed
  // to make one batch of this noodle.
  unsigned int ingredient_cost;

  // The number of servings in one batch.
  unsigned int batch_size;

  // The time needed to cook one batch.
  unsigned int cook_time;

  // The profit from selling one serving.
  unsigned int serving_price;
};


// This class will be passed to your shop to
// tell you about a new order coming in.
struct Order {
  // The unique ID of this order.
  // IDs are strictly increasing.
  unsigned int id;

  // The name of the noodle being ordered.
  std::string noodle;

  // Comparison operator to support std::set.
  bool operator < (const Order& other) const {
    return id < other.id;
  }
};


// Return this class as part of a ServeAction
// to give noodles to a customer.
struct Serve {
  // The ID of the order you're fulfilling.
  unsigned int order_id;

  // The ID of the pot you're serving from.
  unsigned int pot_id;
};

#endif
