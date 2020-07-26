#include "Operator.h"

Operator::Operator(char token, AST* lhs, AST* rhs) {

    mToken = token;
    mLHS = lhs;
    mRHS = rhs;

}

int Operator::arity() const {

    /*if (token == "~") {

        return 1;

    }*/

    return 2;

}

int Operator::associativity() const {

    return 79;

}

int Operator::precedence() const {

    return 79;

} 

// Required member functions.
string Operator::infix() const {

    return "operator";

}

string Operator::postfix() const {

    if (mToken == '~') {

        return mRHS->postfix() + " ~";

    }

    return mLHS->postfix() + ' ' + mRHS->postfix() + ' ' + mToken;

}

string Operator::prefix() const {

    if (mToken == '~') {

        return "~ " + mRHS->prefix();

    }

    return mToken + string(" ") + mLHS->prefix() + ' ' + mRHS->prefix();

}
