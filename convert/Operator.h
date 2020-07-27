#ifndef OPERATOR_H
#define OPERATOR_H

#include "AST.h"

using namespace std;

class Operator: public AST {

  char mToken;
  AST* mLHS;
  AST* mRHS;

public:
  
  Operator(char token, AST* lhs, AST* rhs);
  ~Operator();

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;

  // Required member functions.
  string infix()   const;
  string postfix() const;
  string prefix()  const;
};

#endif
