#ifndef MYGENEPOOL_H
#define MYGENEPOOL_H

#include "GenePool.h"
#include "MyPerson.h"
#include <map>

using namespace std;

class MyGenePool: public GenePool {

  map <string, MyPerson*> genePool;

public:

  MyGenePool(istream& stream);
  ~MyGenePool();

  // Required Function
  MyPerson* find(const std::string& name) const;

  // Other Member Functions

};

#endif
