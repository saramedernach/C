#include "Person.h"
#include "GenePool.h"
#include "Query.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

// This file provides a standard main loop.
// You can edit it if you want, but you shouldn't need to.
// Gradescope will use the original version.


// Helper class to sort person pointers by name:
struct Compare {
  bool operator () (const Person* a, const Person* b) const {
    if(a == nullptr || b == nullptr) {
      throw std::invalid_argument("Null pointer in result set.");
    }

    return a->name() < b->name();
  }
};

// Helper function for cleaner autograder output:
void prompt(const char* message) {
#ifndef NOPROMPT
  std::cout << message;
#else
  (void) message;
#endif
}

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "USAGE: ./genepool [filename]\n";
    std::exit(1);
  }

  GenePool* pool;

  try {
    // Read the database file:
    std::ifstream stream(argv[1]);
    pool = GenePool::create(stream);
  }
  catch(const std::exception& e) {
    std::cerr << "Error reading database: " << e.what() << "\n";
    std::exit(1);
  }

  std::string line;
  prompt("Query: ");
  while(std::getline(std::cin, line)) {
    try {
      // Parse and run the query:
      Query query(line);
      std::set<Person*> result = query.run(*pool);

      // Sort the people by name for consistent output:
      std::vector<Person*> people(result.begin(), result.end());
      std::sort(people.begin(), people.end(), Compare());

      // Print the result:
      std::cout << query.to_string() << ":\n";
      for(Person* person: people) {
        std::cout << " - " << person->name() << std::endl;
      }
      if(people.empty()) {
        std::cout << " (no results)\n";
      }
    }
    catch(const std::exception& e) {
      // Print the error message:
      std::cout << e.what() << std::endl;
    }

    prompt("Query: ");
  }

  prompt("\n");
  delete pool;
  return 0;
}
