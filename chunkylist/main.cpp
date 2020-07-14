#include "MyChunkyList.h"
#include <iostream>

using namespace std;

int main() {

    MyChunkyList list(3);
    MyChunkyNode node("a", 0, 3, nullptr, nullptr);
    cout<< node.items()[0];

    return 0;

}