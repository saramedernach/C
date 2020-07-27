#include "AST.h"
#include "Number.h"
#include "Operator.h"
#include <stack>
#include <stdexcept>
#include <iostream>

// Helper functions (recommended):
bool is_operator(const std::string& token) {

    if (token.length() != 1) {

        return false;

    }

    switch(token[0]) {

        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '~':
            
            return true;

        default:

            return false;

    }

}

bool is_number(const std::string& token) {

    try {

        size_t len = 0;
        stod(token, &len);
        return (len == token.length());

    }
    catch (const invalid_argument&) {

        return false;

    }


}

AST* AST::parse_prefix(std::istream& tokens) {

    string token;

    if (!(tokens >> token)) {

        cout << "Not enough operands."  << endl;
        return 0;

    }

    tokens >> token;

    if (token == "~") {
        
        AST* rhs = AST::parse_prefix(tokens);
        return new Operator('~', nullptr, rhs);

    }
    else if(is_operator(token)) {

        AST* lhs = AST::parse_prefix(tokens);
        AST* rhs = AST::parse_prefix(tokens);
        return new Operator(token[0], lhs, rhs);

    }       
    else if (is_number(token)) {

        return new Number(token);

    }

    return new Number(token);

}

AST* AST::parse_postfix(std::istream& tokens) {

    stack<AST*> stack;
    string token;

    try {

        while (tokens >> token) {

            if (token == "~") {

                AST* rhs = stack.top();
                stack.pop();

                AST* ast = new Operator('~', nullptr, rhs);
                stack.push(ast);

            }
            else if (is_operator(token)) {

                AST* rhs = stack.top();
                stack.pop();

                AST* lhs = stack.top();
                stack.pop();

                AST* ast = new Operator(token[0], lhs, rhs);
                stack.push(ast);

            }
            else if (is_number(token)) {

                stack.push(new Number(token));

            }
            else {

                cout << "Invalid token: " << token << endl;
                break;

            }

        }

        if (stack.size() < 1) {

            //throw runtime_error("Not enough operands.");
            cout << "Not enough operands." << endl;
            

        }
        else if (stack.size() > 1) {

            //throw runtime_error("Too many operands.");
            cout << "Too many operands." << endl;
            

        }
        else {

            return stack.top();

        }

    }
    catch (const runtime_error&) {

        while(!stack.empty()) {

            delete stack.top();
            stack.pop();

        }

    }

    throw;

}
