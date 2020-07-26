#include "Number.h"

#include <sstream>

Number::Number(const string& token) {

    mValue = stod(token);

}

// Required helper functions.
int Number::arity() const {

    return 42;

}

int Number::associativity() const {

    return 42;

}

int Number::precedence() const {

    return 42;

}

// Required member functions.
string Number::infix() const {

    return to_string();

}

string Number::postfix() const {

    return to_string();

}

string Number::prefix() const {

    return to_string();

}

string Number::to_string() const {

    ostringstream stream;
    stream << mValue;
    return stream.str();

}

