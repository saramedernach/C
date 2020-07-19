#include "MyStack.h"


Node::Node(double token, Node* next) {

    mToken = token;
    mNext = next;

}

Node* Node::next() const {

    return mNext;

}

double Node::token() {

    return mToken;

}

MyStack::MyStack() {

    mTop = nullptr;

}

MyStack::~MyStack() {

    clear();

}

void MyStack::clear() {
    
    while(!is_empty()) {

        pop();

    }

}

bool MyStack::is_empty() const {

    return mTop == nullptr;

}

void MyStack::push(double item) {

    Node* node = new Node(item, mTop);
    mTop = node;

}

double MyStack::pop() {

    if (is_empty()) {

        throw underflow_error("Underflow Error.");

    }
    else {

        Node* node = mTop;
        mTop = mTop->next();
        double nodeToken = node->token();
        delete node;
        return nodeToken;
        
    }

}

double MyStack::top() const {

    if (is_empty()) {

        throw underflow_error("Underflow Error.");

    }
    else {

        return mTop->token();

    }

}