#include <iostream>
#include <cstring>
#include <string>
using namespace std;

string reverse(string name);

int main(int argc, char *argv[]) {

    cout << reverse(argv[1]) << endl;

    return 0;

}

string reverse(string name) {

    string str = "Hello, " + name + "!";

    string backwards = "";

    for (int i = str.length() - 1; i >= 0; i--) {

        backwards += str[i];

    }

    return backwards;

}