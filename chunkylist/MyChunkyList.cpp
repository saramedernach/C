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

    if (index < 0 || index > mChunksize) {

        throw out_of_range("Invalid index.");

    }

}
