#include "AST.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  
  if (argc != 3) {

    cerr << "Usage: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }
  /*if (argc != 3 || (((strcmp(argv[1], "prefix") != 0) || (strcmp(argv[1], "postfix") != 0)) && ((strcmp(argv[2], "prefix") != 0) || (strcmp(argv[2], "postfix") != 0) || (strcmp(argv[2], "infix") != 0)))) {

    cerr << "Usage: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }
  else if (strcmp(argv[1], "prefix") != 0 || strcmp(argv[1], "prefix") != 0){

    cerr << "Usage: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }
  else if (strcmp(argv[2], "prefix") != 0 || strcmp(argv[2], "prefix") != 0 || strcmp(argv[2], "infix") != 0) {

    cerr << "Usage: convert [input-format] [output-format]\n"
      << "  Valid input formats:   prefix, postfix\n"
      << "  Valid output formats:  prefix, infix, postfix\n";
    exit(0);

  }*/

  std::string line;
  while(std::getline(std::cin, line)) {
    std::istringstream tokens(line);

    AST* ast = AST::parse_postfix(tokens);
    cout << "=> " << ast->prefix() << endl;
    

  }
}
