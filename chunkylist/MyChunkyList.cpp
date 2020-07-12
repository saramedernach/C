#include "MyChunkyList.h"

#include <stdexcept>

MyChunkyList::MyChunkyList(int chunksize) {

    mHead = nullptr;
    mTail = nullptr;
    mCount = 0;
    mChunksize = chunksize;

}

MyChunkyList::~MyChunkyList() {

    delete mHead;
    delete mTail;

}

int MyChunkyList::count() const {

    return mCount;

}

void MyChunkyList::insert(int index, const string& item) {

    int mNodeIndex = mCount % mChunksize;

    if (index < 0 || index > mCount) {

        throw out_of_range("Invalid index.");

    }

    if (index == 0) {

        if (mNodeIndex == 0) {

            mHead = new MyChunkyNode(item, mNodeIndex, mChunksize, mHead, mTail);
            

        }

        

    }

    else {

    }

    mCount += 1;

}
