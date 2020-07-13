#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"
#include <string>

using namespace std;

class MyChunkyNode: public ChunkyNode {
  
  string* mItem;
  int nodeIndex;
  MyChunkyNode* mPrev;
  MyChunkyNode* mNext;

public:

  MyChunkyNode(const string& item, int nodeIndex, int chunksize, MyChunkyNode* prev, MyChunkyNode* next);

  ~MyChunkyNode();

  int count() const;
  string* items() const;
  MyChunkyNode* prev() const;
  MyChunkyNode* next() const;
  void setNext(MyChunkyNode* next);
  void setPrev(MyChunkyNode* prev);

};

#endif
