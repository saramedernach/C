#ifndef MYCHUNKYLIST_H
#define MYCHUNKYLIST_H

#include "ChunkyList.h"
#include "MyChunkyNode.h"

#include <cstring>
#include <string>
using namespace std;

class MyChunkyList: public ChunkyList {
  // TODO: Member Variables
public:
  
  MyChunkyList(int chunksize);
  ~MyChunkyList();

  int count() const;
  void insert(int index, const string& item);
  string& lookup(int index);
  void remove(int index);

  ChunkyNode* head() const;
  ChunkyNode* tail() const;

};

#endif
