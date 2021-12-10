#include "ET.h"

ET::ET(GLint bottom, GLint top) {
    for (GLint y = bottom; y <= top; y++) {
        BucketNode* newBucket = new BucketNode(y);
        if (head == nullptr) {
            head = tail = newBucket;
        } else {
            tail->setNext(newBucket);
            tail = newBucket;
        }
    }
}

BucketNode* ET::getHead() const {
    return head;
}

void ET::setHead(BucketNode* head) {
    this->head = head;
}

BucketNode* ET::getTail() const {
    return tail;
}

void ET::setTail(BucketNode* tail) {
    this->tail = tail;
}