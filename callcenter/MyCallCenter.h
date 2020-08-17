#ifndef MYCALLCENTER_H
#define MYCALLCENTER_H

#include "CallCenter.h"

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;

class CompareImportance {

public:
  
  bool operator () (Call *c1, Call *c2) {

    return c1->importance < c2->importance;

  }

};

class MyCallCenter: public CallCenter {

  // Member Variables
  vector<Employee> mEmployees;
  map<int, Call*> mPool;
  vector<priority_queue<Call*, vector<Call*>, CompareImportance> > hold;
  vector<int> work;

public:

  // Constructor
  MyCallCenter(vector<Employee> employees);

  // Destructor
  ~MyCallCenter();

  // Required Member Functions
  std::vector<int> calls(int minute, const std::vector<int>& call_ids);
  void learn(int minute, const std::vector<Call>& calls);

  // Other Member Functions
};

#endif
