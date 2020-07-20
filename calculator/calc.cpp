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

    MyStack stack;
    stringstream s(line);
    string token;
    regex regex_number("[+-]?[0-9]+(\\.[0-9]+)?([Ee][+-]?[0-9]+)?");
    
    int flag = 0;

    if (line.empty() || line == "   ") {

      cout << "No expression." << endl;

    }

    while (s >> token) {

      if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "~") {

        if (stack.is_empty()) {

          cout << "Not enough operands." << endl;
          flag = 1;
          break;

        }

        double rightOperand;

        if (!stack.is_empty()) {

          rightOperand = stack.pop();

        }

        double result = 0;

        if (token == "~"){

          result = -rightOperand;
          stack.push(result);
          continue;
          
        }

        if (stack.is_empty()) {

          cout << "Not enough operands." << endl;
          flag = 1;
          break;

        }

        double leftOperand;

        if (!stack.is_empty()) {

          leftOperand = stack.pop();

        }

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

          if (rightOperand == 0 || rightOperand == -0) {

            cout << "Division by zero." << endl;
            flag = 1;
            break;

          }
          else {

            result = leftOperand / rightOperand;

          }
          
        }
        else if (token == "%"){

          if (rightOperand == 0 || rightOperand == -0) {

            cout << "Division by zero." << endl;
            flag = 1;
            break;

          }
          else {

            result = fmod(leftOperand, rightOperand);

          }
          
        }
        else if (token == "^"){
          
          result = pow(leftOperand, rightOperand);
          
        }

        stack.push(result);

      }
      else if (regex_match(token, regex_number))
      {
        
        stack.push(stod(token));

      }
      else {

        cout << "Unknown token." << endl;
        flag = 1;
        break;

      }


    }

    if (stack.count() > 1) {

      if (flag == 0) {

        cout << "Too many operands." << endl;

      }

      continue;

    }

    else if (!stack.is_empty()) {

      if (flag == 0) {

        cout << "= " << stack.pop() << endl;

      }

      continue;

    }

    continue;
    
  }

}
