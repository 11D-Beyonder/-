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
	* ��������㷨������������������±ߣ�
	* ��Bucket�գ�ֱ����ӣ�
	* ���򣬰���xInYMin����˳���ţ�
	* shiftFactorΪ�ڶ����ȼ�������С�����š�
	*/
	if (head == nullptr) {
		newEdge->setNext(nullptr);
		head = tail = newEdge;
		return;
	}

	GLdouble xInYMin = newEdge->getX();
	GLdouble shiftFactor = newEdge->getShiftFactor();

	//�����Ƿ����ͷ
	if (xInYMin < head->getX()) {
		//ֱ�Ӳ���ͷ
		newEdge->setNext(head);
		head = newEdge;
		return;
	} else if (fabs(xInYMin - head->getX()) < eps && shiftFactor < head->getShiftFactor()) {
		//���յڶ��ؼ���ֱ�Ӳ���ͷ
		newEdge->setNext(head);
		head = newEdge;
		return;
	}

	//�����Ƿ����β
	if (xInYMin > tail->getX()) {
		//���յ�һ�ؼ��ֲ���β
		tail->setNext(newEdge);
		tail = newEdge;
		newEdge->setNext(nullptr);
		return;
	} else if (fabs(xInYMin - tail->getX()) < eps && shiftFactor > tail->getShiftFactor()) {
		//���յڶ��ؼ��ֲ���β
		tail->setNext(newEdge);
		tail = newEdge;
		newEdge->setNext(nullptr);
		return;
	}

	//�����м䲿�� ͬʱ�Ƚ������߱�
	for (EdgeNode* cur = head; cur->getNext() != nullptr; cur = cur->getNext()) {
		if (cur->getX() < xInYMin && xInYMin < cur->getNext()->getX()) {
			//���յ�һ�ؼ��ֱȽ�
			newEdge->setNext(cur->getNext());
			cur->setNext(newEdge);
			return;
		} else if (fabs(cur->getX() - xInYMin) < eps) {
			//����cur��һ�ؼ�����ͬ
			//���յڶ��ؼ��ֱȽ� cur
			if (fabs(cur->getNext()->getX() - xInYMin) < eps) {
				//���յڶ��ؼ��ֱȽ� cur->next
				if (cur->getShiftFactor() < shiftFactor && shiftFactor < cur->getNext()->getShiftFactor()) {
					newEdge->setNext(cur->getNext());
					cur->setNext(newEdge);
					return;
				}
			} else {
				//����cur->next->XInYMin>xInYMin
				newEdge->setNext(cur->getNext());
				cur->setNext(newEdge);
				return;
			}
		}
	}
}