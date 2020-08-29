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

};

struct Road {

  City* source;
  City* destination;
  int route_id;
  int road_id;
  unsigned int days;
  unsigned int load;
  unsigned int cost;
  bool used;

};

class MyScheduler: public Scheduler {

  // Member Variables
  unsigned int mDeadline;
  map<string, City> mCities;
  vector<Route> mRoutes;
  unordered_map<int, Road> roads;
  vector<Road> mFactories;
  vector<pair<Road, int> > path;
  list<pair<Road, int> > *adj;
  int day;
  int doses;

public:

  // Constructor
  MyScheduler(unsigned int deadline, map<string, unsigned int> cities, vector<string> factories, vector<Route> routes);

  // Required Member Function
  vector<Shipment> schedule();

  void shortestPath(vector<Road> sources);
  vector<Shipment> recursiveShipment(Road *road);

};

class CompareDays {

public:

  bool operator () (pair<int, Road> &r1, pair<int, Road> &r2) {

    return r1.first > r2.first;

  }

};

#endif
