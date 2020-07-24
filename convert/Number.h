#ifndef NUMBER_H
#define NUMBER_H

#include "AST.h"

using namespace std;


class Number: public AST {
  
  double mValue;

public:
  
  Number(const string& token);

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;

  // Required member functions.
  string infix()   const;
  string postfix() const;
  string prefix()  const;
  string to_string() const;
};

#endif
