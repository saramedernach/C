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

    Pot p;
    p.potID = potID;
    pots.push_back(p);

  }

  /*for (auto& noodle: noodles) {

    MyNoodle info;
    info.mCookTime = noodle.cook_time;
    info.mBatchSize = noodle.batch_size;
    info.mIngredientCost = noodle.ingredient_cost;
    info.mServingPrice = noodle.serving_price;
    info.mName = noodle.name;

    noodleOrder[noodle.name] = info;

  }*/

}
// MyNoodleShop Member Functions
vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> orderlist) {

  /*for (Order order: orderlist) {

    auto itr = noodleOrder.find(order.noodle);

    MyOrder info;
    info.id = order.id;
    info.noodle = order.noodle;
    info.minute = minute;

    MyNoodle& noodle = itr->second;
    noodle.orders.push(info);

  }*/

  vector<Order> acceptedOrders;
  for (Order order: orderlist) {

    if (onlyOption == "") {

      onlyOption = order.noodle;

      auto itr = mNoodles.begin();

      for (auto& noodle: mNoodles) {

        if (onlyOption != noodle.name) {

          itr++;

        }
        else {
          break;
        }

      }

      Noodle& noodle = (*itr);

      MyNoodle info;
      info.mCookTime = noodle.cook_time;
      info.mBatchSize = noodle.batch_size;
      info.mIngredientCost = noodle.ingredient_cost;
      info.mServingPrice = noodle.serving_price;
      info.mName = noodle.name;

      noodleOrder[noodle.name] = info;

    }

    if (order.noodle == onlyOption) {

      auto it = noodleOrder.find(onlyOption);

      MyOrder info;
      info.id = order.id;
      info.noodle = order.noodle;
      info.minute = minute;

      MyNoodle& noodle = it->second;
      noodle.orders.push(info);

      acceptedOrders.push_back(order);

    }

  }

  return acceptedOrders;

  //return orderlist;

}

Action* MyNoodleShop::action(int minute) {
  
  auto itr = noodleOrder.begin();
  MyNoodle& noodle = itr->second;

  /*for (auto& pot: inUsePots) {

    if (inUsePots.empty()) {

      break;

    }

    while (pot.second.noodle == noodle.mName && pot.second.potID < mNpots) {

      itr++;
      noodle = itr->second;

    }

  }*/

  auto it = pots.begin();
 
  if ((it->dirty && it->servings == 0) || it->staleAt < minute) {

    it->dirty = false;
    it->staleAt = noodle.mCookTime + 30 + minute;
    it->servings = 0;
    Action* clean = new CleanAction(it->potID);
    return clean;

  }
  else if (it->servings == 0) {

    it->dirty = true;
    it->cookTime = noodle.mCookTime;
    it->servings = noodle.mBatchSize;
    it->readyAt = noodle.mCookTime + minute;
    it->staleAt = it->readyAt + 30;
    it->noodle = noodle.mName;

    inUsePots[it->noodle] = *it;

    Action* cook = new CookAction(it->potID, it->noodle);
    return cook;

  }
  else if (it->readyAt >= minute || !noodle.orders.empty()) {

    vector<Serve> serveVector;

    if (noodle.orders.empty()) {
      
      Action* none = new NoAction();
      return none;
    }

    for (auto& pair: noodleOrder) {

      auto i = inUsePots.find(pair.second.mName);

      if (i == inUsePots.end()) {

        continue;

      }
      
      while (!pair.second.orders.empty()) {

        if (i->second.servings == 0) {

          break;

        }

        Serve serveObject;

        MyOrder info = pair.second.orders.front();
        pair.second.orders.pop();

        serveObject.order_id = info.id;
        serveObject.pot_id = i->second.potID;
        serveVector.push_back(serveObject);
        i->second.servings--;

      }

    }

    Action* serve = new ServeAction(serveVector);
    return serve;

  }
  else {

    Action* none = new NoAction();
    return none;

  }

  pots.push_back(*it);
  pots.erase(it);

  /*if (Cook()) {

    auto itr = pots.begin();

    for (auto& pot: pots) {

        if (pot.dirty) {

            itr++;

        }
        else {

          break;

        }

    }

    auto it = noodleOrder.begin();

    for (auto& noodle: noodleOrder) {

      if (noodle.second.mBatchSize != 0) {

        it++;

      }
      else {

        break;

      }

    }

    itr->dirty = true;
    itr->cookTime = it->second.mCookTime;
    itr->servings = it->second.mServingPrice;
    itr->readyAt = it->second.mCookTime + minute;
    itr->staleAt = itr->readyAt + 30;
    itr->noodle = it->second.mName;

    Action* cook = new CookAction(itr->potID, itr->noodle);

  }
  else if (Serve())*/

}

bool MyNoodleShop::Cook() {

  for (auto& pot: pots) {

    if (!pot.dirty) {

      return false;

    }

  }

  for (auto& noodle: noodleOrder) {

    if (noodle.second.mBatchSize == 0) {

      return false;

    }

  }

  return true;

}

bool MyNoodleShop::ServeY(int minute) {

  for (auto& pot: pots) {

    if (pot.readyAt >= minute && pot.staleAt < minute) {

      auto itr = noodleOrder.begin();

      for (auto& noodle: noodleOrder) {

        if (pot.noodle != noodle.first) {

          itr++;

        }
        else {



        }

      }

    }

  }

}