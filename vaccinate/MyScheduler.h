#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#include "Scheduler.h"

#include <queue>
#include <list>
#include <set>
#include <iostream>

using namespace std;

class CompareDays {

public:

  bool operator () (pair<Route, int> &r1, pair<Route, int> &r2) {

    return r1.second > r2.second;

  }

};

class MyScheduler: public Scheduler {

  struct City {

    string   name;
    bool          factory;
    unsigned int  population;
    unsigned int  vaccines;
    set<Route>    routes;

  };

  // Member Variables
  unsigned int mDeadline;
  map<string, City> mCities;
  vector<Route> mRoutes;
  map<pair<string, string>, int> graph;
  vector<vector<pair<Route, int> > > paths;

public:

  // Constructor
  MyScheduler(unsigned int deadline, map<string, unsigned int> cities, vector<string> factories, vector<Route> routes);

  // Required Member Function
  vector<Shipment> schedule();

  vector<pair<Route, int> > shortestPath(City source);

};

#endif
