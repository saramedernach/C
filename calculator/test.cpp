#include "MyStack.h"

using namespace std;

// Use this file to test your MyStack class!
// This file won't be graded - do whatever you want.

int main() {
  MyStack* stack = new MyStack();

  stack->push(1);
  stack->push(2);

  stack->clear();


  delete stack;
  return 0;
}
