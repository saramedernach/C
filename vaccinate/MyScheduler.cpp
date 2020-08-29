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
    road1.used = false;

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
    road2.used = false;

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

vector<Shipment> MyScheduler::schedule() {

  vector<Shipment> shipments;
  int day = 0;
  
  //for (auto road = path.rbegin(); road != path.rend(); ++road) {
  for (auto& road: path) { 

    Shipment ship;

    cout << dose << endl;
    
    ship.route_id = road.first.route_id;
    ship.source = road.first.source->name;
    ship.day = day;
    ship.doses = dose;

    day += road.second.first;
    dose -= road.second.second;

    shipments.push_back(ship);

  }

  return shipments;
  
}

void MyScheduler::shortestPath(vector<Road> sources) {

  priority_queue<pair<int, Road>, vector<pair<int, Road> >, CompareDays > pq;
  int days = 0;

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
    dose += pq.top().second.doses;
    pq.top().second.destination->prev = &roads[pq.top().second.road_id];
    pq.top().second.destination->visited = true;

    path.push_back(make_pair(pq.top().second, make_pair(pq.top().first, dose)));

    pq.pop();

    for (auto& adjacent: adj[sourceID]) {

      if (adjacent.first.destination->visited == false) {

        pq.push(make_pair(adjacent.second + days, adjacent.first));

      }
      
    }

  }

  for (auto& road: path) {

    cout << road.first.source->name << " -> " << road.first.destination->name << " " << road.first.route_id << " Doses: " << road.second.second << endl;
    //cout << "Previous: " << road.first << endl;

  }

}

vector<Shipment> MyScheduler::recursiveShipment(Road *road) {

  vector<Shipment> shipments;
  (void) road;

  /*if (road->destination->prev == nullptr) {

    Shipment ship;

    ship.route_id = road->route_id;
    ship.source = road->source->name;
    ship.day = day;
    ship.doses = doses;

    shipments.push_back(ship);

  }
  else {

    day += road->days;
    doses += road->destination->population;
    recursiveShipment(road->destination->prev);

  }*/

  return shipments;

}