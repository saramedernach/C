#include "Operator.h"
#include <stack>

Operator::Operator(char token, AST* lhs, AST* rhs) {

    mToken = token;
    mLHS = lhs;
    mRHS = rhs;

}

Operator::~Operator() {

    if(mRHS == nullptr && mLHS == nullptr) {

        delete this;

    }
    else {

        delete mLHS;
        delete mRHS;
    }

}

int Operator::arity() const {

    if (mToken == '~') {

        return 1;

    }

    return 2;

}

int Operator::associativity() const {

    if (mToken == '~') {

        return 1;

    }

    return -1;

}

int Operator::precedence() const {

    if (mToken == '+' || mToken == '-') {

        return 1;

    }
    else if (mToken == '*' || mToken == '/' || mToken == '%') {

        return 2;

    }
    else if (mToken == '~') {

        return 3;

    }
    
    return 4;

} 

// Required member functions.
string Operator::infix() const {

    if (mLHS == nullptr || mRHS == nullptr) {

        if (mRHS != nullptr) {

            return "~ " + mRHS->infix();

        }

        return to_string(mToken);

    }
    else if (mLHS->precedence() > this->precedence() || mRHS->precedence() > this->precedence()) {

        if (mToken == '~') {

            return "~ " + mRHS->infix();

        }

        return mLHS->infix() + ' ' + mToken + ' ' + mRHS->infix();

    }
    else if (mLHS->precedence() < this->precedence() || mRHS->precedence() < this->precedence()) {

        if (mToken == '~') {

            return "(~ " + mRHS->infix() + ")";

        }

        return '(' + mLHS->infix() + ' ' + mToken + ' ' + mRHS->infix() + ')';

    }
    else {

        if (mLHS->associativity() < 0 || mRHS->associativity() > 0) {

            if (mToken == '~') {

                return "~ " + mRHS->infix();

            }

            return mLHS->infix() + ' ' + mToken + ' ' + mRHS->infix();

        }
        else {

            if (mToken == '~') {

                return "(~ " + mRHS->infix() + ")";

            }

            return '(' + mLHS->infix() + ' ' + mToken + ' ' + mRHS->infix() + ')';

        }

    }

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
