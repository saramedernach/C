#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(const string& item, int nodeIndex, int chunksize, MyChunkyNode* prev, MyChunkyNode* next) {

    mItem = new string[chunksize];
    mItem[nodeIndex] = item;
    mPrev = prev;
    mNext = next;

}

MyChunkyNode::~MyChunkyNode() {

    //delete mPrev;
    delete mNext;

}

int MyChunkyNode::count() const {

    int n = 0;

    while (mItem[n] != "\0") {

        n++;

    }

    return n;

}

string* MyChunkyNode::items() const {

    return mItem;

}

MyChunkyNode* MyChunkyNode::prev() const {

    return mPrev;

}

MyChunkyNode* MyChunkyNode::next() const {

    return mNext;

}

void MyChunkyNode::setNext(MyChunkyNode* next) {

    mNext = next;

}

void MyChunkyNode::setPrev(MyChunkyNode* prev) {

    mPrev = prev;

}