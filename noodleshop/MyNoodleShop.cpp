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

  return orderlist;

}

Action* MyNoodleShop::action(int minute) {



}

