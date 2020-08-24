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
    city.name = pair.first;
    city.factory = false;
    city.population = pair.second;
    city.vaccines = 0;
    city.prev = nullptr;

    mCities[pair.first] = city;

  }

  for(const auto& name: factories) {

    auto itr = mCities.find(name);

    itr->second.factory = true;

  }

  for (auto route: mRoutes) {

    auto itr = mCities.find(route.city1);
    auto it = mCities.find(route.city2);

    Road road;
    road.source = &itr->second;
    road.destination = &it->second;
    road.days = route.days;
    road.route_id = route.id;
    road.load = route.load;
    road.cost = route.cost;

    itr->second.roads.push_back(road);
    it->second.roads.push_back(road);

  }

  for (const auto& city: mCities) {

    if (city.second.factory) {

      paths.push_back(shortestPath(city.second));

    }

  }

}

vector<Shipment> MyScheduler::schedule() {

  vector<Shipment> shipments;
  
  for (auto& path: paths) {

    int doses = 0;
    int day = 0;

    for (auto rit = path.rbegin(); rit != path.rend(); ++rit) {

      if (rit->first.source->prev == nullptr) {

        doses += rit->first.destination->population;

        Shipment ship;

        ship.route_id = rit->first.route_id;
        ship.source = rit->first.source->name;
        ship.day = day;
        ship.doses = doses;

        shipments.push_back(ship);

      }
      else {

        doses += rit->first.destination->population;
        day += rit->first.days;
        continue;

      }

    }

  }

  return shipments;

}

vector<pair<Road, int> > MyScheduler::shortestPath(City source) {

  vector<pair<Road, int> > path;
  priority_queue<pair<Road, int>, vector<pair<Road, int> >, CompareDays > pq;
  int days = 0;

  for (auto& road: source.roads) {

    days = road.days;
    pq.push(make_pair(road, road.days));

  }
  
  while (!pq.empty()) {

    int flag = 0;

    for (const auto& pair: path) {
      
      if (pair.first.destination->name == pq.top().first.destination->name) {
        
        pq.pop();
        pq.pop();
        flag = 1;
        continue;

      }

    }

    if (flag == 1) {

      break;

    }


    path.push_back(make_pair(pq.top().first, days));

    auto itr = mCities.find(pq.top().first.destination->name);
    for (auto& road: itr->second.roads) {

      days += road.days;
      pq.push(make_pair(road, days));

    }

    if (pq.empty()) {

      break;

    }

    pq.pop();

  }
  
  

  for (const auto pair: path) {

    auto it = mCities.find(pair.first.source->name);
    auto itr = mCities.find(pair.first.destination->name);
    itr->second.prev = &it->second;
    cout << pair.first.source->name << " -> " << pair.first.destination->name << " " << pair.second << endl;

  }

  return path;

}