#include "AST.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  
  if (argc != 3) {

    cerr << "USAGE: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }

  if (strcmp(argv[1], "prefix") != 0 && strcmp(argv[1], "postfix") != 0) {

    cerr << "USAGE: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }

  if (strcmp(argv[2], "prefix") != 0 && strcmp(argv[2], "postfix") != 0 && strcmp(argv[2], "infix") != 0) {

    cerr << "USAGE: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }


  std::string line;
  while(std::getline(std::cin, line)) {
    std::istringstream tokens(line);

    AST* ast;
    string token;

    try {

      if (strcmp(argv[1], "prefix") == 0) {

        try {

          ast = AST::parse_prefix(tokens);
          
          if (tokens >> token) {

            cout << "Too many operands." << endl;
            delete ast;
            continue;

          }
        
        }
        catch (const runtime_error& r) {

          cout << r.what();
          continue;

        }

      }
      else {

        ast = AST::parse_postfix(tokens);

      }

      if (strcmp(argv[2], "prefix") == 0) {

        if (ast == nullptr) {

              continue;     

        }

        cout << "=> " << ast->prefix() << endl;

      }
      else if (strcmp(argv[2], "infix") == 0) {

        if (ast == nullptr) {

              continue;     

        }

        cout << "=> " << ast->infix() << endl;

      }
      else if (strcmp(argv[2], "postfix") == 0) {

        if (ast == nullptr) {

              continue;     

        }

        cout << "=> " << ast->postfix() << endl;

      }

      delete ast;
    
    }
    catch (runtime_error& e) {

      cout << e.what();

    }

  }
}
