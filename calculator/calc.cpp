#include "Stack.h"
#include "MyStack.h"
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;



int main() {
  
  string line;
  while (getline(cin, line)) {

    MyStack* stack = new MyStack();
    stringstream s(line);
    string token;
    regex regex_number("[+-]?[0-9]+(\\.[0-9]+)?([Ee][+-]?[0-9]+)?");

    while (s >> token) {

      if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "~") {

        double rightOperand = stack->pop();
        double result = 0;

        if (token == "~"){

          result = -rightOperand;
          
        }

        if (stack->is_empty()) {

          cout << "Not enough operands." << endl;
          getline(cin, line);

        }

        double leftOperand = stack->pop();

        if (token == "+") {

          result = leftOperand + rightOperand;

        }
        else if (token == "-"){

          result = leftOperand - rightOperand;

        }
        else if (token == "*"){

          result = leftOperand * rightOperand;
          
        }
        else if (token == "/"){

          if (rightOperand == 0) {

            cout << "Division by zero" << endl;
            getline(cin, line);

          }
          else {

            result = leftOperand / rightOperand;

          }
          
        }
        else if (token == "%"){

          if (rightOperand == 0) {

            cout << "Division by zero" << endl;
            getline(cin, line);

          }
          else {

            result = fmod(leftOperand, rightOperand);

          }
          
        }
        else if (token == "^"){

          result = pow(leftOperand, rightOperand);
          
        }

        stack->push(result);

      }
      else if (regex_match(token, regex_number))
      {
        
        stack->push(stod(token));

      }
      else if (line.empty()) {

        cout << "No expression" << endl;
        getline(cin, line);

      }
      else {

        cout << "Unknown token." << endl;
        getline(cin, line);

      }


    }

      cout << "= " << stack->pop() << endl;
    
    /*else {

      cout << "Too many operands" << endl;

    }*/
    
  }

}
