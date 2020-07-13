#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"
#include <string>

using namespace std;

class MyChunkyNode: public ChunkyNode {
  
  string* mItem;
  MyChunkyNode* mPrev;
  MyChunkyNode* mNext;

public:

  MyChunkyNode(const string& item, int nodeIndex, int chunksize, MyChunkyNode* prev, MyChunkyNode* next);

  ~MyChunkyNode();

  int count() const;
  string* items() const;
  ChunkyNode* prev() const;
  ChunkyNode* next() const;
  void setNext(ChunkyNode* next);
  void setPrev(ChunkyNode* prev);

};

#endif
