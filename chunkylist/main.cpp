#include "MyChunkyList.h"
#include <iostream>

using namespace std;

int main() {

    MyChunkyList list(3);
    MyChunkyNode node("a", 0, 3, nullptr, nullptr);
    cout << node.count();

    return 0;

}