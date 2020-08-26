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

  for (auto& noodle: noodles) {

    MyNoodle info;
    info.mCookTime = noodle.cook_time;
    info.mBatchSize = noodle.batch_size;
    info.mIngredientCost = noodle.ingredient_cost;
    info.mServingPrice = noodle.serving_price;
    info.mServings = 0;
    info.mName = noodle.name;

    noodleOrder[noodle.name] = info;

  }

}
// MyNoodleShop Member Functions
vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> orderlist) {

  for (Order order: orderlist) {

    auto itr = noodleOrder.find(order.noodle);

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

  if (cook()) {

    vector<Pot>::iterator itr;
    for (auto it = pots.begin(); it != pots.end(); ++it) {

      if (!it->dirty) {
        
        itr = it;
        break;

      }

    } 

    map<string, MyNoodle>::iterator it;
    for (auto i = noodleOrder.begin(); i != noodleOrder.end(); ++i) {

      unsigned long temp = i->second.mServings;
      if (temp < i->second.orders.size()) {

        it = i;
        break;

      }

    }

    itr->dirty = true;
    itr->cookTime = it->second.mCookTime;
    itr->servings = it->second.mBatchSize;
    itr->readyAt = it->second.mCookTime + minute;
    itr->staleAt = itr->readyAt + 30;
    itr->noodle = it->second.mName;

    it->second.mServings += it->second.mBatchSize;

    Action* cook = new CookAction(itr->potID, itr->noodle);
    return cook;

  }
  else if (needClean(minute)) {

    for (auto& pot: pots) {

      if (pot.dirty && pot.staleAt < minute) {

        noodleOrder[pot.noodle].mServings -= pot.servings;
        pot.dirty = false;
        pot.staleAt = noodleOrder[pot.noodle].mCookTime + 30 + minute;
        pot.servings = 0;

        Action* clean = new CleanAction(pot.potID);
        return clean;

      }

    }

  }
  else if (serveOrder(minute)) {

    vector<Serve> serveVector;

    for (auto& pot: pots) {

      if (minute >= pot.readyAt && minute < pot.staleAt && pot.servings > 0) {

        auto itr = noodleOrder.begin();

        for (auto& noodle: noodleOrder) {

          if (pot.noodle != noodle.first) {

            itr++;

          }
          else {

            break;

          }

        }

        while (!itr->second.orders.empty()) {

          Serve serveObject;

          MyOrder info = itr->second.orders.front();
          itr->second.orders.pop();

          serveObject.order_id = info.id;
          serveObject.pot_id = pot.potID;
          serveVector.push_back(serveObject);
          itr->second.mServings--;
          pot.servings--;

        }

      }

    }

    if (!serveVector.empty()) {

      Action* serve = new ServeAction(serveVector);
      return serve;

    }
    else {

      Action* none = new NoAction();
      return none;

    }

  }
  else if (clean(minute)) {

    for (auto& pot: pots) {

      if (pot.dirty && pot.staleAt < minute) {

        auto itr = noodleOrder.begin();
        
        for (auto& noodle: noodleOrder) {

          if (pot.noodle != noodle.first) {

            itr++;

          }
          else {

            break;

          }

        }

        pot.dirty = false;
        pot.staleAt = itr->second.mCookTime + 30 + minute;
        itr->second.mServings -= pot.servings;
        pot.servings = 0;

        Action* clean = new CleanAction(pot.potID);
        return clean;

      }

    }

  }

  Action* none = new NoAction();
  return none;

}

bool MyNoodleShop::cook() {

  int m = 0;
  int n = 0;

  for (auto& pot: pots) {

    if (!pot.dirty) {

      m = 1;

    }

  }

  for (auto& noodle: noodleOrder) {

    unsigned long temp = noodle.second.mServings;
    if (temp < noodle.second.orders.size()) {

      n = 1;

    }

  }

  if (m == 1 && n == 1) {

    return true;

  }

  return false;

}

bool MyNoodleShop::serveOrder(int minute) {

  for (auto& pot: pots) {

    if (minute >= pot.readyAt && minute < pot.staleAt && pot.servings > 0) {

      auto itr = noodleOrder.begin();

      for (auto& noodle: noodleOrder) {

        if (pot.noodle != noodle.first) {

          itr++;

        }
        else {

          break;

        }

      }

      if (!itr->second.orders.empty()) {

        return true;

      }

    }

  }

  return false;

}

bool MyNoodleShop::clean(int minute) {

  for (auto& pot: pots) {

    if (pot.dirty && pot.staleAt < minute) {

      return true;

    }

  }

  return false;

}

bool MyNoodleShop::needClean(int minute) {

  int n = 0;
  int m = 0;

  for (auto& noodle: noodleOrder) {

    if (noodle.second.mServings == 0 && !noodle.second.orders.empty()) {

      n = 1;

    }

  }

  for (auto& pot: pots) {

    if (pot.dirty && pot.staleAt < minute) {

      m = 1;

    }

  }

  if (n == 1 && m == 1) {

    return true;

  }

  return false;

}