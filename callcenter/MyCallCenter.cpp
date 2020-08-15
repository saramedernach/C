#include "MyCallCenter.h"

CallCenter* CallCenter::create(std::vector<Employee> employees) {

  return new MyCallCenter(employees);

}

// MyCallCenter Member Functions
MyCallCenter::MyCallCenter(vector<Employee> employees) {

  mEmployees = employees;
  hold.resize(26);
  work.reserve(mEmployees.size());

  for (unsigned long i = 0; i < mEmployees.size(); i++) {

    work.push_back(0);

  }

}

MyCallCenter::~MyCallCenter() {

  for(const Employee& employee: mEmployees) {

    delete employee.call;

  }

  for(const auto& pair: mPool) {

    delete pair.second;

  }

}

vector<int> MyCallCenter::calls(int minute, const std::vector<int>& call_ids) {
  
  /*auto itr = call_ids.begin();
  auto i = mPool.find(*itr);

  if (i == mPool.end()) {*/

    for (int id: call_ids) {

      mPool[id] = new Call();

      auto it = mPool.find(id);
      it->second->id = id;
      it->second->recieved = minute;
      it->second->importance = -1;
      it->second->difficulty = 1;
      it->second->work_required = -1;
      it->second->work_performed = 0;
      
      hold[it->second->difficulty].push(mPool[id]);

    }
  
  //}
  //else {

    for (Employee& employee: mEmployees) {

      if ((employee.call == nullptr || work[employee.id] == -1) && !hold[employee.skill].empty()) {
        
        employee.call = hold[employee.skill].top();
        hold[employee.skill].pop();

        work[employee.id] = employee.call->id;
        
      }
      if (employee.call == nullptr) {

        continue;

      }
      if (employee.call->difficulty > employee.skill) {

        cout << "1" << endl;

        for (Employee& e: mEmployees) {

          if (e.skill >= employee.call->difficulty && e.call->id == 0) {

            hold[employee.call->difficulty].push(employee.call);
            e.call = hold[e.skill].top();
            hold[e.skill].pop();
            employee.call->id = 0;

            work[e.id] = e.call->id;
            work[employee.id] = 0;

            break;

          }

        }

        if (employee.call->difficulty > employee.skill) {

          hold[employee.call->difficulty].push(employee.call);
          employee.call->id = 0;

          work[employee.id] = 0;

        }

      }
      if (employee.call->work_performed == employee.call->work_required) {

        work[employee.id] = -1;

      }
      if (employee.call->work_performed != employee.call->work_required){

        employee.call->work_performed++;

      }

    }

  //}

  return work;

}

void MyCallCenter::learn(int minute, const std::vector<Call>& calls) {
  
  (void) minute;
  
  for (const Call& call: calls) {

    mPool[call.id] = new Call(call);

  }

}
