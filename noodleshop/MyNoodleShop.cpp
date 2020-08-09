#include "MyNoodleShop.h"

#include <iostream>

// This is here to avoid creating yet another object file.
NoodleShop* NoodleShop::create(int npots, int rent, int customers, std::vector<Noodle> noodles) {
  return new MyNoodleShop(npots, rent, customers, noodles);
}

MyNoodleShop::MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles) {

  mNpots = npots;
  mRent = rent;
  mCustomers = customers;
  mNoodles = noodles;

  for (int potID = 0; potID < mNpots; potID++) {

    Pot* p = new Pot();
    pots.push_back(*p);
    p->potID = potID;


  }

}

// MyNoodleShop Member Functions
vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> orderlist) {

  for (Order order: orderlist) {

    auto itr = noodleOrder.find(order.noodle);

    if (itr == noodleOrder.end()) {

      vector<Noodle>::iterator it;

      for (auto i = mNoodles.begin(); i < mNoodles.end(); i++) {

        if (i->name == order.noodle) {

          it = i;
          break;

        }

      }
      MyNoodle noodle;
      noodle.mName = it->name;
      noodle.mBatchSize = it->batch_size;
      noodle.mCookTime = it->cook_time;
      noodle.mIngredientCost = it->ingredient_cost;
      noodle.mServingPrice = it->serving_price;

      noodleOrder[order.noodle] = noodle;
      itr = noodleOrder.find(order.noodle);

    }

    MyOrder info;
    info.id = order.id;
    info.noodle = order.noodle;
    info.minute = minute;

    MyNoodle& noodle = itr->second;
    noodle.orders.push(info);


  }

  return orderlist;

}

Action* MyNoodleShop::action(int minute) {

  auto itr = noodleOrder.begin();
  MyNoodle& noodle = itr->second;

  auto it = pots.begin();

  if (it->dirty || it->staleAt > minute) {

    it->dirty = false;
    Action* clean = new CleanAction(it->potID);
    return clean;

  } 
  else if (it->servings == 0) {

    it->dirty = true;
    it->servings = noodle.mBatchSize;
    it->readyAt = noodle.mCookTime + minute;
    it->staleAt = it->readyAt + 30;
    it->noodle = noodle.mName;

    Action* cook = new CookAction(it->potID, noodle.mName);
    cout << "5" << endl;
    return cook;

  }
  else if (it->readyAt >= minute) {

    vector<Serve> serveVector;
    Serve serveObject;

    cout << noodle.orders.size() << endl;

    if (noodle.orders.empty()) {
      
      Action* none = new NoAction();
      return none;
    }

    MyOrder info = noodle.orders.front();
    noodle.orders.pop();

    serveObject.order_id = info.id;
    serveObject.pot_id = it->potID;
    serveVector.push_back(serveObject);

    if (noodle.orders.empty()) {

      noodleOrder.erase(itr);
      Action* none = new NoAction();
      return none;

    }

    it->servings --;

    Action* serve = new ServeAction(serveVector);
    return serve;

  }
  else {

    Action* none = new NoAction();
    return none;

  }

  pots.push_back(*it);
  pots.erase(it);

}

