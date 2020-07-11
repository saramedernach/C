#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(const string& item, ChunkyNode* prev, ChunkyNode* next) {

    mItem = item;
    mPrev = prev;
    mNext = next;

}

MyChunkyNode::~MyChunkyNode() {

    delete mPrev;
    delete mNext;

}
