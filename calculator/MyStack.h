#ifndef MYSTACK_H
#define MYSTACK_H

#include "Stack.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Node {

  double mToken;
  Node* mNext;

public:

  Node(double token, Node* next);
  //~Node();

  Node* next() const;
  double token();
  
};

class MyStack: public Stack {
  
  Node* mTop;

public:
  
  MyStack();
  ~MyStack();

  // Required Stack functions.
  // See Stack.h for descriptions.
  void   clear();
  bool   is_empty() const;
  void   push(double item);
  double pop();
  double top() const;

};

#endif
