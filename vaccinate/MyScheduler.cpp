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

  doses = 0;
  day = 0;

  adj = new list<pair<Road, int> > [mRoutes.size()];
  V = mRoutes.size();
  int id = 1;

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

  for (auto& route: mRoutes) {

    auto itr = mCities.find(route.city1);
    auto it = mCities.find(route.city2);

    Road road;
    road.source = &itr->second;
    road.destination = &it->second;
    road.days = route.days;
    road.route_id = route.id;
    road.load = route.load;
    road.cost = route.cost;

    roads[road.route_id] = road;

    itr->second.roads.push_back(road);
    it->second.roads.push_back(road);

    adj[itr->second.id].push_back(make_pair(road, road.days));
    //adj[it->second.id].push_back(make_pair(road, route.days));

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
  
  

  return shipments;
  
}

void MyScheduler::shortestPath(vector<Road> sources) {

  priority_queue<pair<int, Road>, vector<pair<int, Road> >, CompareDays > pq;
  vector<int> dist(V, INF);

  for (auto& source: sources) {

    for (auto& adjacent: adj[source.source->id]) {

      pq.push(make_pair(adjacent.second, adjacent.first));
      dist[adjacent.first.source->id] = adjacent.second;

    }

  }

  while (!pq.empty()) {

    int sourceID = pq.top().second.source->id;
    pq.top().second.destination->prev = pq.top().second.source;

    pq.pop();

    for (auto& adjacent: adj[sourceID]) {

      Road dest = adjacent.first;
      int destID = adjacent.first.route_id;
      int days = adjacent.second;

      if (dist[destID] > dist[sourceID] + days && dest.destination->visited == false) {

        dist[destID] = dist[sourceID] + days;
        pq.push(make_pair(dist[destID], dest));

      }

    } 

  }

}