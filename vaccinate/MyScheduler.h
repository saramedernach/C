#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#include "Scheduler.h"

#include <queue>
#include <list>
#include <set>
#include <iostream>
#include <unordered_map>

using namespace std;
#define INF 0x3f3f3f3f

struct City;
struct Road;

struct City {

  string name;
  int id;
  bool factory;
  unsigned int population;
  unsigned int vaccines;
  bool visited;
  Road* prev;
  vector<Road> roads;

};

struct Road {

  City* source;
  City* destination;
  int route_id;
  unsigned int days;
  unsigned int load;
  unsigned int cost;

  /*bool operator < (Road const &r2) const {

    if (this->days < r2.days) {

      return true;

    }

    return false;

  }*/

};

class MyScheduler: public Scheduler {

  // Member Variables
  unsigned int mDeadline;
  map<string, City> mCities;
  vector<Route> mRoutes;
  unordered_map<int, Road> roads;
  vector<Road> mFactories;
  list<pair<Road, int> > *adj;
  int V;
  int doses;
  int day;

public:

  // Constructor
  MyScheduler(unsigned int deadline, map<string, unsigned int> cities, vector<string> factories, vector<Route> routes);

  // Required Member Function
  vector<Shipment> schedule();

  void shortestPath(vector<Road> sources);

};

class CompareDays {

public:

  bool operator () (pair<int, Road> &r1, pair<int, Road> &r2) {

    return r1.first > r2.first;

  }

};

#endif
