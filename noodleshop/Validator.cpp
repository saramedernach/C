#include "Validator.h"

// Visitor callbacks for the Action classes:
void CleanAction::validate(Validator* validator) const {validator->validate(this);}
void CookAction::validate( Validator* validator) const {validator->validate(this);}
void NoAction::validate(   Validator* validator) const {validator->validate(this);}
void ServeAction::validate(Validator* validator) const {validator->validate(this);}


Validator::Validator(unsigned int npots, unsigned int rent, std::vector<Noodle> noodles) {
  for(const auto& noodle: noodles) {
    NoodleInfo info;
    info.cook_time       = noodle.cook_time;
    info.batch_size      = noodle.batch_size;
    info.ingredient_cost = noodle.ingredient_cost;
    info.serving_price   = noodle.serving_price;
    info.profit          = 0;
    info.loss            = 0;

    mNoodles[noodle.name] = info;
  }

  mPots   = std::vector<PotInfo>(npots);
  mMinute = 479; // 7:59 AM
  mRent   = rent;
  mIncome = 0;
  mCoGS   = 0;
}


unsigned int Validator::cogs() const {
  return mCoGS;
}

unsigned int Validator::income() const {
  return mIncome;
}

void Validator::orders(unsigned int minute, const std::vector<Order>& orders) {
  if(minute != ++mMinute) {
    throw std::runtime_error("Time is an illusion!");
  }

  if(minute >= 720 && !orders.empty()) {
    throw std::runtime_error("Orders received after eight PM!");
  }

  for(const auto& order: orders) {
    auto itr = mNoodles.find(order.noodle);
    if(itr == mNoodles.end()) {
      throw std::runtime_error("No such noodle: " + order.noodle);
    }

    OrderInfo info;
    info.id     = order.id;
    info.noodle = order.noodle;
    info.minute = minute;

    NoodleInfo& noodle = itr->second;
    noodle.orders.push(info);
    mOrders[order.id] = info;
  }
}

unsigned int Validator::rent() const {
  return mRent;
}

void Validator::summarize() const {

}

void Validator::validate(const Action* action) {
  action->validate(this);
}

void Validator::validate(const CookAction* action) {
  unsigned int pid = action->pot_id;
  if(pid >= mPots.size()) {
    throw std::runtime_error("Invalid pot ID: " + std::to_string(pid));
  }

  PotInfo& pot = mPots[pid];
  if(pot.noodle != "") {
    throw std::runtime_error("Pot " + std::to_string(pid) + " is not clean.");
  }

  auto itr = mNoodles.find(action->noodle);
  if(itr == mNoodles.end()) {
    throw std::runtime_error("No such noodle: " + action->noodle);
  }

  NoodleInfo& noodle = itr->second;
  noodle.loss += noodle.ingredient_cost;
  mCoGS += noodle.ingredient_cost;

  pot.noodle   = action->noodle;
  pot.ready_at = mMinute + noodle.cook_time;
  pot.stale_at = mMinute + noodle.cook_time + 30;
  pot.servings = noodle.batch_size;
}

void Validator::validate(const CleanAction* action) {
  unsigned int pid = action->pot_id;
  if(pid >= mPots.size()) {
    throw std::runtime_error("Invalid pot ID: " + std::to_string(pid));
  }

  mPots[pid].noodle = "";
}

void Validator::validate(const ServeAction* action) {
  for(const Serve& serve: action->serves) {
    unsigned int pid = serve.pot_id;
    unsigned int oid = serve.order_id;

    if(pid >= mPots.size()) {
      throw std::runtime_error("Invalid pot ID: " + std::to_string(pid));
    }

    auto itr = mOrders.find(oid);
    if(itr == mOrders.end()) {
      throw std::runtime_error("Invalid order ID: " + std::to_string(oid));
    }

    PotInfo& pot = mPots[pid];
    if(pot.noodle == "") {
      throw std::runtime_error("Pot " + std::to_string(pid) + " is empty.");
    }

    OrderInfo& order = itr->second;
    if(pot.noodle != order.noodle) {
      throw std::runtime_error("Order " + std::to_string(oid) + " wanted " + order.noodle + " but got " + pot.noodle + ".");
    }

    NoodleInfo& noodle = mNoodles[order.noodle];
    if(order.id != noodle.orders.front().id) {
      throw std::runtime_error("Order " + std::to_string(oid) + " was served before order " + std::to_string(noodle.orders.front().id) + ".");
    }

    unsigned int wait = mMinute - order.minute;
    unsigned int base = noodle.serving_price;
    unsigned int tips = 0;

    if(wait > 15) {
      base = 0;
    }
    else if(wait < 10) {
      tips = (10 - wait) * 10;
    }
    else {
      // TODO
    }

    mIncome       += base + tips;
    noodle.profit += base + tips;
    noodle.orders.pop();
    mOrders.erase(oid);
    pot.servings -= 1;
  }
}

void Validator::validate(const NoAction* action) {
  // Nothing to do.
}
