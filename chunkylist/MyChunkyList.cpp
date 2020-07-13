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

    if (index < 0 || index > mCount) {

        throw out_of_range("Invalid index.");

    }

    if (index == 0) {

        if (mCount == 0) {

            mHead = new MyChunkyNode(item, 0, mChunksize, nullptr, nullptr);
            

        }
        else if (mHead->count() == mChunksize) {

            mHead = new MyChunkyNode(item, 0, mChunksize, nullptr, mHead);
            //mHead->setPrev(node);
            //mHead = node;

        }
        else {

            int nodeIndex = (mHead->count()) % mChunksize;
            mHead->items()[nodeIndex] = item;

        }
        

        

    }
    else if (index == mCount) {
        
        if ((mTail->count()) == mChunksize) {

            mTail = new MyChunkyNode(item, 0, mChunksize, mTail, nullptr);
            //mTail->setNext(node);
            //node->setPrev(mTail);
            //mTail = node;

        }
        else {

            int nodeIndex = (mTail->count()) % mChunksize;
            mTail->items()[nodeIndex] = item;

        }

    }
    else {

        ChunkyNode* mNode = mHead;
        int n = mNode->count();
        while (n <= index) {

            mNode = mNode->next();
            n += mNode->count();

        }

        if ((mNode->count()) == mChunksize) {

            int half = ((mNode->count()) / 2);
            MyChunkyNode* node = new MyChunkyNode(nullptr, 0, mChunksize, nullptr, nullptr);

            if ((mNode->count()) % 2 != 0) {

                for (int j =  0; j < half; ++j) {

                    node->items()[j] = mNode->items()[j + half + 1];
                    mNode->items()[j + half + 1] = nullptr;

                }

                int nodeIndex = (node->count()) % mChunksize;
                node->items()[nodeIndex] = item;

            }
            else {

                for (int j = 0; j < half - 1; ++j) {

                    node->items()[j] = mNode->items()[j + half + 1];
                    mNode->items()[j + half + 1] = nullptr;

                }

                int nodeIndex = (node->count()) % mChunksize;
                node->items()[nodeIndex] = item;

            }

             mNode = node->prev();

            //node->setPrev(mNode);
            //node->setNext(mNode->next());

        }
        else {

            int nodeIndex = (mNode->count()) % mChunksize;
            mNode->items()[nodeIndex] = item;

        }

    }

    mCount += 1;

}

string& MyChunkyList::lookup(int index) {

    if (index < 0 || index >= mCount) {

        throw out_of_range("Invalid index.");

    }

    ChunkyNode* node = mHead;
    int n = node->count();
    while (n <= index) {

        node = node->next();
        n += node->count();

    }

    ChunkyNode* indexNode = mHead;
    int i = index;
    while (i >= node->count()) {

        i -= indexNode->count();
        indexNode = indexNode->next();

    }

    return node->items()[i];


}

void MyChunkyList::remove(int index) {

    if (index < 0 || index >= mCount) {

        throw out_of_range("Invalid index.");

    }

    /*if (index == 0 ) {

        ChunkyNode* dead = mHead;
        mHead = dead->next();

    }*/
    else {

        ChunkyNode* node = mHead;
        int n = node->count();
        while (n <= index) {

            node = node->next();
            n += node->count();

        }

        ChunkyNode* indexNode = mHead;
        int i = index;
        while (i >= node->count()) {

            i -= indexNode->count();
            indexNode = indexNode->next();

        }

        for (int j = i; j < (node->count() - 1); ++j) {

            node->items()[j] = node->items()[j+1];

        }

        node->items()[node->count() - 1] = nullptr;

        ChunkyNode* mergeNode = mHead;
        ChunkyNode* secondNode = mergeNode->next();
        int first = mergeNode->count();
        int second = secondNode->count();

        while (secondNode != nullptr) {

            if (first + second <= mChunksize / 2) {

                for (int s = 0; s < secondNode->count(); s++) {

                    mergeNode->items()[mergeNode->count() + s] = secondNode->items()[s];

                }

                ChunkyNode* dead = secondNode;
                secondNode = dead->next();

            }
            
            mergeNode = secondNode;

        }

    }

}

ChunkyNode* MyChunkyList::head() const {

    return mHead;

}

ChunkyNode* MyChunkyList::tail() const {

    return mTail;
    
}