#include "MyGenePool.h"
#include "MyPerson.h"

#include <string>
#include <sstream>
#include <iostream>

MyGenePool::MyGenePool(istream& stream) {

  string line;

  while (getline(stream, line)) {

    if (line.empty() || line.find("#") == 0) {

      continue;

    }

    int i = 1;
    string word = "";

    string name;
    Gender gender;
    MyPerson* mother;
    MyPerson* father;
    set<MyPerson*> children;

    for (char x: line) {

      if (x == '\t') {

        if (i == 1) {

          name = word;

        }
        else if (i == 2) {

          if (word == "male") {

            gender = Gender::MALE;

          }
          else if (word == "female") {

            gender = Gender::FEMALE;

          }
          else {

            gender = Gender::ANY;

          }

        }
        else if (i == 3) {

          if (word == "???") {

            mother = nullptr;
              
          }
          else {

            mother = genePool[word];

          }

        }

        i++;
        word = "";

      }
      else {

        word += x;

      }

      if (word == "???") {

        father = nullptr;

      }
      else {

        father = genePool[word];

      }

    }

    MyPerson* person = new MyPerson(name, gender, mother, father, children);
    genePool[name] = person;

    person->mother()->children().insert(person);
    person->father()->children().insert(person);

  }

}

/*MyGenePool::~MyGenePool() {


}*/

// This is here to avoid having yet another object file:
GenePool* GenePool::create(std::istream& stream) {

  return new MyGenePool(stream);

}


// MyGenePool Member Functions

MyPerson* MyGenePool::find(const std::string& name) const {

  return genePool.find(name)->second;

}