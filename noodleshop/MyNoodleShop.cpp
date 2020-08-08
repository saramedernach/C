#include "MyNoodleShop.h"

// This is here to avoid creating yet another object file.
NoodleShop* NoodleShop::create(int npots, int rent, int customers, std::vector<Noodle> noodles) {
  return new MyNoodleShop(npots, rent, customers, noodles);
}

MyNoodleShop::MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles) {

  mNpots = npots;
  mRent = rent;
  mCustomers = customers;
  mNoodles = noodles;

}

// MyNoodleShop Member Functions
vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> orderlist) {

  mOrderList = orderlist;

  for (Order order: orderlist) {

    vector<Noodle>::iterator it = find(mNoodles.begin(), mNoodles.end(), order.noodle);
    int batchSize, cookTime, ingredientCost, servingPrice;

    if (it != mNoodles.end()) {

      batchSize = it->batch_size;
      cookTime = it->cook_time;
      ingredientCost = it->ingredient_cost;
      servingPrice = it->serving_price;

    }

    MyNoodle* mNoodle = new MyNoodle(order.noodle, batchSize, cookTime, ingredientCost, servingPrice);

    if (noodleOrder.find(order.noodle) == noodleOrder.end()) {
      
      queue<MyNoodle*> queueNoodle;
      noodleOrder[order.noodle] = queueNoodle;
      queueNoodle.push(mNoodle);

    }
    else {

      noodleOrder[order.noodle].push(mNoodle);

    } 

  }

  return orderlist;

}

Action* MyNoodleShop::action(int minute) {

  int potID = rand() % 0 + (mNpots - 1);

  for (int potID = 0; potID < mNpots; potID++) {

    
  
  }

  for (Order order: mOrderList) {

    if (mNpots != 0) {

      return CookAction(potID, order.noodle);

    }
    else if ()

  }

}

