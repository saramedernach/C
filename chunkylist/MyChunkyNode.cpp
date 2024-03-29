#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(const string& item, int nodeIndex, int chunksize, MyChunkyNode* prev, MyChunkyNode* next) {

    mItem = new string[chunksize];
    for (int i = 0; i < chunksize; ++i) {

        mItem[i] = "";

    }
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

    while (mItem[n] != "") {

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