#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"
#include <string>

using namespace std;

class MyChunkyNode: public ChunkyNode {
  
  string* mItem;
  ChunkyNode* mPrev;
  ChunkyNode* mNext;

public:

  MyChunkyNode(const string& item, int nodeIndex, int chunksize, ChunkyNode* prev, ChunkyNode* next);

  ~MyChunkyNode();

  int count() const;
  string* items() const;
  ChunkyNode* prev() const;
  ChunkyNode* next() const;

};

#endif
