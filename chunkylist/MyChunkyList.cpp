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
            mTail = mHead;
            

        }
        else if (mHead->count() == mChunksize) {

            MyChunkyNode* oldHead = mHead;
            mHead = new MyChunkyNode(item, 0, mChunksize, nullptr, mHead);
            oldHead->setPrev(mHead);

        }
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

            mHead->items()[i] = item;

        }
        

        

    }
    /*else if (index == mCount) {
        
        if ((mTail->count()) == mChunksize) {

            MyChunkyNode* node = new MyChunkyNode(item, 0, mChunksize, nullptr, nullptr);
            mTail->setNext(node);
            node->setPrev(mTail);
            mTail = node;

        }
        else {

            int nodeIndex = (mTail->count()) % mChunksize;
            mTail->items()[nodeIndex] = item;

        }

    }*/
    else {

        MyChunkyNode* mNode = mHead;
        int n = mNode->count();
        while (n <= index) {

            mNode = mNode->next();
            n += mNode->count();

        }

        ChunkyNode* indexNode = mHead;
        int i = index;
        while (i >= mNode->count()) {

            i -= indexNode->count();
            indexNode = indexNode->next();

        }

        if (mNode->next() == nullptr) {


            if (mNode->count() == mChunksize) {

                MyChunkyNode* node = new MyChunkyNode(item, 0, mChunksize, nullptr, nullptr);
                mNode->setNext(node);
                node->setPrev(mNode);
                mTail = node;

            }
            else {

                int nodeIndex = (mNode->count()) % mChunksize;
                mNode->items()[nodeIndex] = item;

            }

        }

        if ((mNode->count()) == mChunksize) {

            MyChunkyNode* node = new MyChunkyNode(nullptr, 0, mChunksize, nullptr, nullptr);

            if ((mNode->count()) % 2 != 0) {

                MyChunkyNode* temp = new MyChunkyNode(nullptr, 0, mChunksize + 1, nullptr, nullptr);
                int w = 0;

                while (w < i) {

                    temp->items()[w] = mNode->items()[w];
                    w++;

                }

                temp->items()[i] = item;
                for (int p = i + 1; p < mNode->count(); ++p) {

                    temp->items()[p] = mNode->items()[p];

                }

                int half = ((temp->count()) / 2);

                for (int j =  0; j < half; ++j) {

                    node->items()[j] = mNode->items()[j + half + 1];
                    mNode->items()[j + half + 1] = nullptr;

                }

            }
            else {

                MyChunkyNode* temp = new MyChunkyNode(nullptr, 0, mChunksize + 1, nullptr, nullptr);
                int w = 0;

                while (w < i) {

                    temp->items()[w] = mNode->items()[w];
                    w++;

                }

                temp->items()[i] = item;
                for (int p = i + 1; p < mNode->count(); ++p) {

                    temp->items()[p] = mNode->items()[p];

                }

                int half = ((temp->count()) / 2);

                for (int j = 0; j < half - 1; ++j) {

                    node->items()[j] = mNode->items()[j + half + 1];
                    mNode->items()[j + half + 1] = nullptr;

                }

            }

            node->setNext(mNode->next());
            node->setPrev(mNode);

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

    if (index == 0 ) {

        if (mHead->count() == 0) {

            MyChunkyNode* dead = mHead;
            mHead = dead->next();

        }
        else {

            for (int r = 0; r < (mHead->count() - 1); ++r) {

                mHead->items()[r] = mHead->items()[r+1];

            }

            mHead->items()[mHead->count() - 1] = nullptr;

        }

    }
    else {

        MyChunkyNode* node = mHead;
        int n = node->count();
        while (n <= index) {

            node = node->next();
            n += node->count();

        }

        MyChunkyNode* indexNode = mHead;
        int i = index;
        while (i >= node->count()) {

            i -= indexNode->count();
            indexNode = indexNode->next();

        }

        for (int j = i; j < (node->count() - 1); ++j) {

            node->items()[j] = node->items()[j+1];

        }

        node->items()[node->count() - 1] = nullptr;

        MyChunkyNode* mergeNode = mHead;
        MyChunkyNode* secondNode = mergeNode->next();
        int first = mergeNode->count();
        int second = secondNode->count();

        while (secondNode != nullptr) {

            if (first + second <= mChunksize / 2) {

                for (int s = 0; s < secondNode->count(); s++) {

                    mergeNode->items()[mergeNode->count() + s] = secondNode->items()[s];

                }

                if (secondNode == mTail) {

                    mTail = mergeNode;
                    mTail->setPrev(mergeNode->prev());
                    mTail->setPrev(nullptr);

                }
                else {

                    mergeNode->setNext(secondNode->next());

                }

            }

        }

    }

}

ChunkyNode* MyChunkyList::head() const {

    return mHead;

}

ChunkyNode* MyChunkyList::tail() const {

    return mTail;
    
}