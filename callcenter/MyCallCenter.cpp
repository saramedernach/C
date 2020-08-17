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
    it->second->work_required = -1;
    it->second->work_performed = -1;;
    
    hold[it->second->difficulty].push(mPool[id]);

  }

  for (Employee& employee: mEmployees) {

    if ((employee.call == nullptr || work[employee.id] == -1)) {

      for (int i = employee.skill; i >= 0; i--) {
        
        if (!hold[i].empty()) {

          if (i == 0) {

            auto itr = mPool.find(hold[0].top()->id);

            if (itr->second->work_performed != -1) {

              hold[0].pop();
              continue;

            }

          }

          int j = 0;
          for (auto e: mEmployees) {

            if (e.call == hold[i].top()) {

              e.call = new Call(*mPool[hold[i].top()->id]);
              j = 1;
              break;

            }

          }

          if (j == 1) {

            continue;

          }

          employee.call = new Call(*mPool[hold[i].top()->id]);
          hold[i].pop();
          work[employee.id] = employee.call->id;
          continue;

        }

      }
      
    }
    if (employee.call == nullptr) {

      continue;

    }
    if (employee.call->work_required != -1 && employee.call != nullptr) {
      
      int j = 0;
      for (auto e: mEmployees) {

        if (e.call == employee.call) {

          employee.call = new Call(*mPool[employee.call->id]);
          j = 1;
          break;

        }

      }

      if (j == 1) {

        continue;

      }

      employee.call = new Call(*mPool[employee.call->id]);

    }
    //cout << "Call: " << employee.call->id << endl;
    //cout << employee.name << ": " << employee.call->difficulty << " > " << employee.skill << endl;
    if (employee.call->difficulty > employee.skill) {
      
      for (Employee& e: mEmployees) {

        if (e.skill >= employee.call->difficulty) {

          hold[employee.call->difficulty].push(employee.call);
          e.call = new Call(*mPool[hold[employee.call->difficulty].top()->id]);
          hold[employee.call->difficulty].pop();
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
    else if (employee.call->work_performed + 1 == employee.call->work_required) {

      work[employee.id] = -1;

    }
    else if (employee.call->work_performed != employee.call->work_required){

      employee.call->work_performed++;

    }

  }

  return work;

}

void MyCallCenter::learn(int minute, const std::vector<Call>& calls) {
  
  (void) minute;
  
  for (const Call& call: calls) {

    mPool[call.id] = new Call(call);

    hold[mPool[call.id]->difficulty].push(mPool[call.id]);

  }

}
