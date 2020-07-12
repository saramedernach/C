#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(const string& item, int nodeIndex, int chunksize, ChunkyNode* prev, ChunkyNode* next) {

    mItem = new string[chunksize];
    mItem[nodeIndex] = item;
    mPrev = prev;
    mNext = next;

}

MyChunkyNode::~MyChunkyNode() {

    delete mPrev;
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

ChunkyNode* MyChunkyNode::prev() const {

    return mPrev;

}

ChunkyNode* MyChunkyNode::next() const {

    return mNext;

}