#include "MyNoodleShop.h"

NoodleShop* NoodleShop::create(
  unsigned int npots,
  unsigned int rent,
  unsigned int customers,
  std::vector<Noodle> noodles
) {
  return new MyNoodleShop(/* TODO */);
}


// MyNoodleShop Member Functions
