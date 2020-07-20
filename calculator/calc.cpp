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

    if (line.empty()) {

      cout << "No expression." << endl;
      //getline(cin, line);

    }

    int tokenCount = 0;
    int spaceCount = 0;
    
    while (s >> token) {

      if (token == " ") {

        spaceCount++;

      }

      tokenCount++;

    }

    if (tokenCount == spaceCount) {

      cout << "No expression." << endl;

    }

    while (s >> token) {

      if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "~") {

        if (stack.is_empty()) {

          cout << "Not enough operands." << endl;
          //getline(cin, line);
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
          //getline(cin, line);
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
            //getline(cin, line);
            break;

          }
          else {

            result = leftOperand / rightOperand;

          }
          
        }
        else if (token == "%"){

          if (rightOperand == 0 || rightOperand == -0) {

            cout << "Division by zero." << endl;
            //getline(cin, line);
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
        //getline(cin, line);
        break;

      }


    }

    if (stack.count() > 1) {

      cout << "Too many operands." << endl;
      continue;
      getline(cin, line);

    }
    else if (!stack.is_empty()) {

      cout << "= " << stack.pop() << endl;

    }
    
  }

}
