#include "MyCallCenter.h"

CallCenter* CallCenter::create(std::vector<Employee> employees) {

  return new MyCallCenter(employees);

}

// MyCallCenter Member Functions
MyCallCenter::MyCallCenter(vector<Employee> employees) {

  mEmployees = employees;

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

  auto itr = call_ids.begin();
  auto i = mPool.find(*itr);

  if (i == mPool.end()) {

    for (const int& id: call_ids) {

      mPool[id] = new Call();

      auto it = mPool.find(id);
      it->second->id = id;
      it->second->recieved = minute;
      it->second->importance = -1;
      it->second->difficulty = -1;
      it->second->work_required = -1;
      it->second->work_performed = 0;

      hold.push(mPool[id]);

    }

    for (const Employee& employee: mEmployees) {

      work[employee.id] = 0;

    }
  
  }
  else {

    for (const Employee& employee: mEmployees) {

      if ((employee.call == nullptr || work[employee.id] == -1) && !hold.empty()) {

        employee.call->id = hold.top()->id;
        hold.pop();

        work[employee.id] = employee.call->id;

      }
      else if (employee.call->importance == -1) {

      

      }
      else if (employee.call->difficulty > employee.skill) {

        for (const Employee& e: mEmployees) {

          if (e.skill >= employee.call->difficulty && e.call->id == 0) {

            hold.push(employee.call);
            e.call->id = hold.top()->id;
            hold.pop();
            employee.call->id = 0;

            work[e.id] = e.call->id;
            work[employee.id] = 0;

            break;

          }

        }

        if (employee.call->difficulty > employee.skill) {

          hold.push(employee.call);
          employee.call->id = 0;

          work[employee.id] = 0;

        }

      }
      else if (employee.call->work_performed == employee.call->work_required) {

        work[employee.id] = -1;

      }
      else {

        employee.call->work_performed++;

      }

    }

  }

  return work;

}

void MyCallCenter::learn(int minute, const std::vector<Call>& calls) {

  (void) minute;
  
  for (const Call& call: calls) {

    auto it = mPool.find(call.id);
    int recieved = it->second->recieved;

    mPool[call.id] = new Call(call);
    it->second->recieved = recieved;

  }

}
