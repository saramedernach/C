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

  adj = new list<pair<Road, int> > [cities.size()];
  int id = 0;

  for (const auto& pair: cities) {

    City city;
    city.name = pair.first;
    city.id = id;
    city.factory = false;
    city.population = pair.second;
    city.vaccines = 0;
    city.doses = 0;
    city.roadLength = 0;
    city.day = 0;
    city.visited = false;
    city.prev = nullptr;

    mCities[pair.first] = city;

    id++;

  }

  for(const auto& name: factories) {

    auto itr = mCities.find(name);

    itr->second.factory = true;
    itr->second.visited = true;

  }

  int roadID = 0;
  for (auto& route: mRoutes) {

    auto itr = mCities.find(route.city1);
    auto it = mCities.find(route.city2);

    Road road1;
    road1.source = &itr->second;
    road1.destination = &it->second;
    road1.days = route.days;
    road1.route_id = route.id;
    road1.road_id = roadID;
    road1.load = route.load;
    road1.cost = route.cost;
    road1.doses = road1.destination->population;

    roads[road1.road_id] = road1;
    roadID++;

    Road road2;
    road2.source = &it->second;
    road2.destination = &itr->second;
    road2.days = route.days;
    road2.route_id = route.id;
    road2.road_id = roadID;
    road2.load = route.load;
    road2.cost = route.cost;
    road2.doses = road2.destination->population;

    roads[road2.road_id] = road2;
    roadID++;

    adj[itr->second.id].push_back(make_pair(road1, road1.days));
    adj[it->second.id].push_back(make_pair(road2, road2.days));

  }

  for (const auto& city: mCities) {

    if (city.second.factory) {
      
      for (auto& road: roads) {

        if (road.second.source->name == city.first) {

          mFactories.push_back(road.second);

        }

      }

    }

  }

  shortestPath(mFactories);

}

MyScheduler::~MyScheduler() {

  delete adj;

}

vector<Shipment> MyScheduler::schedule() {

  vector<Shipment> shipments;

  for (auto& city: mCities) {

    int day = 0;
    recursiveDoses(&city.second, city.second.population, day);
    city.second.day = day;

  }

  for (auto& road: path) {

    Shipment ship;

    ship.route_id = road.first.route_id;
    ship.source = road.first.source->name;
    ship.day = road.first.source->day;
    ship.doses = road.first.destination->doses;

    shipments.push_back(ship);

  }

  return shipments;
  
}

void MyScheduler::shortestPath(vector<Road> sources) {

  priority_queue<pair<int, Road>, vector<pair<int, Road> >, CompareDays > pq;
  int days = 0;
  int doses = 0;

  for (auto& source: sources) {

    for (auto& adjacent: adj[source.source->id]) {

      pq.push(make_pair(adjacent.second, adjacent.first));

    }

  }

  while (!pq.empty()) {

    if (pq.top().second.destination->visited == true) {
        
      pq.pop();
      continue;

    }

    int sourceID = pq.top().second.destination->id;
    days += pq.top().first;
    doses += pq.top().second.doses;
    pq.top().second.destination->prev = roads[pq.top().second.road_id].source;
    pq.top().second.destination->roadLength = pq.top().second.days;
    pq.top().second.destination->visited = true;

    path.push_back(make_pair(pq.top().second, make_pair(pq.top().first, doses)));

    pq.pop();

    for (auto& adjacent: adj[sourceID]) {

      if (adjacent.first.destination->visited == false) {

        pq.push(make_pair(adjacent.second + days, adjacent.first));

      }
      
    }

  }

  /*for (auto& road: path) {

    cout << road.second.first << endl;

    cout << road.first.source->name << " -> " << road.first.destination->name << endl;
    if (road.first.source->prev != nullptr)
    cout << "Previous: " << road.first.destination->prev->name << " -> " << road.first.source->prev->name << endl;

  }*/

}

void MyScheduler::recursiveDoses(City* city, int doses, int& day) {

  if (city->prev != nullptr) {

    city->doses += doses;
    day += city->roadLength;
    recursiveDoses(city->prev, doses, day);

  }

}