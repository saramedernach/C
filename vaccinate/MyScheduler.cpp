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
    city.prev = nullptr;

    mCities[pair.first] = city;

    id++;

  }

  for(const auto& name: factories) {

    auto itr = mCities.find(name);

    itr->second.factory = true;

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

  int roadID = 0;
  for (const auto& city: mCities) {

    if (city.second.factory) {
    
      roadID--;
      auto itr = mCities.find(city.first);

      Road road;
      road.source = nullptr;
      road.destination = &itr->second;
      road.days = 0;
      road.route_id = roadID;

      roads[road.route_id] = road;
      adj[0].push_back(make_pair(road, road.days));

      paths.push_back(shortestPath(road));

    }

  }

}

vector<Shipment> MyScheduler::schedule() {

  vector<Shipment> shipments;
  

  return shipments;


  
}

vector<int> MyScheduler::shortestPath(Road source) {

  priority_queue<pair<int, Road>, vector<pair<int, Road> >, CompareDays > pq;
  vector<int> dist(V, INF);
  vector<int> path;

  pq.push(make_pair(0, source));
  dist[source.route_id] = 0;

  while (!pq.empty()) {

    int sourceID = pq.top().second.source->id;
    path.push_back(pq.top().second.route_id);

    pq.pop();

    for (auto& adjacent: adj[sourceID]) {

      int destID = adjacent.first.route_id;
      int days = adjacent.second;

      if (dist[destID] > dist[sourceID] + days) {

        dist[destID] = dist[sourceID] + days;
        pq.push(make_pair(dist[destID], adjacent.first));

      }

    } 

  }

  for (auto& id: path) {

    cout << id << endl;

  }

  return path;

}