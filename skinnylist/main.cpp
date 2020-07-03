#include "SkinnyList.h"

#include <iostream>
#include <string>
#include <vector>

// This collects strings from a list into a vector.
// We do this so we can use the == operator on the result.
std::vector<std::string> items(SkinnyList* list) {
  std::vector<std::string> items;
  for(int i = 0; i < list->count(); ++i) {
    items.push_back(list->lookup(i));
  }

  return items;
}

// This prints a vector of strings, followed by a newline.
void print_vector(const std::vector<std::string>& items) {
  for(const auto& item: items) {
    std::cout << item << ' ';
  }

  std::cout << '\n';
}

// This function will print an error and kill the program if
// it encounters and unexpected data in the list.
void assert_equal(SkinnyList* list, std::vector<std::string> expected) {
  std::vector<std::string> actual = items(list);

  if(list->count() != int(expected.size())) {
    std::cout << "ERROR: Incorrect list count!\n";
    std::cout << "  Expected: " << expected.size() << '\n';
    std::cout << "    Actual: " << list->count() << '\n';
    std::exit(1);
  }

  if(actual.size() != expected.size()) {
    std::cout << "ERROR: Incorrect number of items collected!\n";
    std::cout << "  Expected: " << expected.size() << '\n';
    std::cout << "    Actual: " << actual.size() << '\n';
    std::exit(1);
  }

  if(actual != expected) {
    std::cout << "ERROR: Incorrect list data!\n";
    std::cout << "  Expected: ";
    print_vector(expected);
    std::cout << "    Actual: ";
    print_vector(actual);
    std::exit(1);
  }
}

// This main function is full of tests.
// Run it to make sure SkinnyList works as expected!
int main() {
  // Make a new list...
  SkinnyList* list = new SkinnyList();

  // Test inserting at head...
  list->insert(0, "c");
  list->insert(0, "b");
  list->insert(0, "a");
  assert_equal(list, {"a", "b", "c"});

  // Test inserting at tail...
  list->insert(3, "d");
  list->insert(4, "e");
  list->insert(5, "f");
  assert_equal(list, {"a", "b", "c", "d", "e", "f"});

  // Test inserting in the middle...
  list->insert(2, "!");
  list->insert(5, "?");
  assert_equal(list, {"a", "b", "!", "c", "d", "?", "e", "f"});

  // Test removing the head...
  list->remove(0);
  assert_equal(list, {"b", "!", "c", "d", "?", "e", "f"});

  // Test removing the tail...
  list->remove(6);
  assert_equal(list, {"b", "!", "c", "d", "?", "e"});

  // Test removing in the middle...
  list->remove(4);
  list->remove(1);
  assert_equal(list, {"b", "c", "d", "e"});

  // Test removing everything...
  list->remove(2);
  list->remove(2);
  list->remove(0);
  list->remove(0);
  assert_equal(list, {});

  // All done - clean up!
  std::cout << "All tests passed!\n";
  delete list;
}
