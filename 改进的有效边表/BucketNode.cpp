#include "BucketNode.h"

BucketNode::BucketNode(const GLdouble& y) {
	head = nullptr;
	tail = nullptr;
	next = nullptr;
	this->y = y;
}

GLint BucketNode::getY() const {
	return y;
}

void BucketNode::setY(GLint y) {
	this->y = y;
}

EdgeNode* BucketNode::getHead() const {
	return head;
}

void BucketNode::setHead(EdgeNode* head) {
	this->head = head;
}

BucketNode* BucketNode::getNext() const {
	return next;
}

void BucketNode::setNext(BucketNode* next) {
	this->next = next;
}

void BucketNode::addEdge(EdgeNode* newEdge) {
	/*
	* 设计增量算法，在有序链表中填充新边；
	* 若Bucket空，直接添加；
	* 否则，按照xInYMin递增顺序存放；
	* shiftFactor为第二优先级，按由小到大存放。
	*/
	if (head == nullptr) {
		newEdge->setNext(nullptr);
		head = tail = newEdge;
		return;
	}

	GLdouble xInYMin = newEdge->getX();
	GLdouble shiftFactor = newEdge->getShiftFactor();

	//检验是否插入头
	if (xInYMin < head->getX()) {
		//直接插入头
		newEdge->setNext(head);
		head = newEdge;
		return;
	} else if (fabs(xInYMin - head->getX()) < eps && shiftFactor < head->getShiftFactor()) {
		//按照第二关键字直接插入头
		newEdge->setNext(head);
		head = newEdge;
		return;
	}

	//检验是否插入尾
	if (xInYMin > tail->getX()) {
		//按照第一关键字插入尾
		tail->setNext(newEdge);
		tail = newEdge;
		newEdge->setNext(nullptr);
		return;
	} else if (fabs(xInYMin - tail->getX()) < eps && shiftFactor > tail->getShiftFactor()) {
		//按照第二关键字插入尾
		tail->setNext(newEdge);
		tail = newEdge;
		newEdge->setNext(nullptr);
		return;
	}

	//插入中间部分 同时比较两条边表
	for (EdgeNode* cur = head; cur->getNext() != nullptr; cur = cur->getNext()) {
		if (cur->getX() < xInYMin && xInYMin < cur->getNext()->getX()) {
			//按照第一关键字比较
			newEdge->setNext(cur->getNext());
			cur->setNext(newEdge);
			return;
		} else if (fabs(cur->getX() - xInYMin) < eps) {
			//对于cur第一关键字相同
			//按照第二关键字比较 cur
			if (fabs(cur->getNext()->getX() - xInYMin) < eps) {
				//按照第二关键字比较 cur->next
				if (cur->getShiftFactor() < shiftFactor && shiftFactor < cur->getNext()->getShiftFactor()) {
					newEdge->setNext(cur->getNext());
					cur->setNext(newEdge);
					return;
				}
			} else {
				//必有cur->next->XInYMin>xInYMin
				newEdge->setNext(cur->getNext());
				cur->setNext(newEdge);
				return;
			}
		}
	}
}