#include "MyStack.h"

using namespace std;

// Use this file to test your MyStack class!
// This file won't be graded - do whatever you want.

int main() {
  MyStack* stack = new MyStack();

  stack->push(1);

  stack->pop();


  delete stack;
  return 0;
}
