#include "MyChunkyList.h"
#include <iostream>

using namespace std;

int main() {

    MyChunkyList list(2);
    list.insert(0, "Molly");
    list.insert(0, "Hannah");
    list.insert(0, "Bob");
    list.remove(0);

    return 0;

}