#include "MyCallCenter.h"

CallCenter* CallCenter::create(std::vector<Employee> employees) {

  return new MyCallCenter(employees);

}

// MyCallCenter Member Functions
MyCallCenter::MyCallCenter(vector<Employee> employees) {

  mEmployees = employees;
  hold.resize(100);

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

  for (int id: call_ids) {

    mPool[id] = new Call();

    auto it = mPool.find(id);
    it->second->id = id;
    it->second->recieved = minute;
    it->second->importance = -1;
    it->second->difficulty = 0;
    it->second->work_required = -999;
    it->second->work_performed = -1;;
    
    hold[it->second->difficulty].push(mPool[id]);

  }

  for (Employee& employee: mEmployees) {

    if (employee.call == nullptr || work[employee.id] == -1) {

      for (int i = employee.skill; i >= 0; i--) {
        
        if (!hold[i].empty()) {

          employee.call = mPool[hold[i].top()->id];
          hold[i].pop();
          work[employee.id] = employee.call->id;
          continue;

        }

      }
      
    }
    if (employee.call == nullptr) {

      continue;

    }
    if (work[employee.id] == -1) {

      employee.call = nullptr;
      work[employee.id] = 0;
      continue;

    }
    
    if (employee.call->difficulty > employee.skill && employee.call != nullptr) {
      
      hold[employee.call->difficulty].push(employee.call);
      employee.call = nullptr;
      work[employee.id] = 0;
      continue;

    }
    else if (employee.call->work_performed == employee.call->work_required + 1 && employee.call != nullptr) {

      work[employee.id] = -1;

    }
    else {

      employee.call->work_performed++;

    }

  }

  return work;

}

void MyCallCenter::learn(int minute, const std::vector<Call>& calls) {
  
  (void) minute;
  
  for (const Call& call: calls) {

    //hold[call.difficulty].push(new Call(call));

    *mPool[call.id] = call;

    //hold[mPool[call.id]->difficulty].push(mPool[call.id]);

  }

}
