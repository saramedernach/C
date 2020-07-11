#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"

class MyChunkyNode: public ChunkyNode {
  // TODO: Member Variables
public:
  // TODO: Member Function Declarations

  int count() const;
  string* items() const;
  ChunkyNode* prev() const;
  ChunkyNode* next() const;

};

#endif
