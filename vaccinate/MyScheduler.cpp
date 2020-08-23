#include "MyScheduler.h"

Scheduler* Scheduler::create(
  unsigned int                        deadline,
  std::map<std::string, unsigned int> cities,
  std::vector<std::string>            factories,
  std::vector<Route>                  routes
) {
  return new MyScheduler(MyScheduler(deadline, cities, factories, routes));
}

// MyScheduler Member Functions
MyScheduler::MyScheduler(unsigned int deadline, map<string, unsigned int> cities, vector<string> factories, vector<Route> routes) {

  mDeadline = deadline;
  mRoutes = routes;

  for (const auto& pair: cities) {

    City city;
    city.name       = pair.first;
    city.factory    = false;
    city.population = pair.second;
    city.vaccines   = 0;

    mCities[pair.first] = city;

  }

  for(const auto& name: factories) {

    auto itr = mCities.find(name);

    itr->second.factory = true;

  }

  for (auto route: mRoutes) {

    auto itr = mCities.find(route.city1);
    auto it = mCities.find(route.city2);

    itr->second.routes.insert(route);
    it->second.routes.insert(route);

  }

  for (const auto& city: mCities) {

    if (city.second.factory) {

      paths.push_back(shortestPath(city.second));

    }

  }

}

vector<Shipment> MyScheduler::schedule() {

  vector<Shipment> shipments;
  Shipment ship;
  shipments.push_back(ship);
  
  /*for (auto& path: paths) {

    

  }*/

  return shipments;

}

vector<pair<Route, int> > MyScheduler::shortestPath(City source) {

  vector<pair<Route, int> > path;
  priority_queue<pair<Route, int>, vector<pair<Route, int> >, CompareDays > pq;
  int days = 0;

  for (auto& route: source.routes) {

    days = route.days;
    pq.push(make_pair(route, route.days));

  }

  while (!pq.empty()) {

    for (const auto& pair: path) {

      if (pair.first.city2 == pq.top().first.city2) {

        pq.pop();

      }

    }

    path.push_back(make_pair(pq.top().first, days));

    auto itr = mCities.find(pq.top().first.city2);
    for (auto& route: itr->second.routes) {

      days += route.days;
      pq.push(make_pair(route, days));

    }

    pq.pop();

  }

  for (auto p: path) {

    cout << p.first.city1 << " -> " << p.first.city2 << " " << p.second;

  }
  return path;

}