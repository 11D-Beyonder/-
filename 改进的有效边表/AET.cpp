#include "AET.h"

AET::AET() {
	curY = 0;
	head = tail = nullptr;
}

AET::AET(BucketNode* bucket) {
	head = tail = nullptr;
	this->curY = bucket->getY();
	for (EdgeNode* edge = bucket->getHead(); edge != nullptr; edge = edge->getNext()) {
		addEdge(new EdgeNode(edge));
	}
}

AET::~AET() {
	for (EdgeNode* p = head; p != nullptr;) {
		EdgeNode* temp = p;
		p = p->getNext();
		delete temp;
		temp = nullptr;
	}
}

EdgeNode* AET::getHead() const {
	return head;
}

void AET::setHead(EdgeNode* head) {
	this->head = head;
}

EdgeNode* AET::getTail() const {
	return tail;
}

void AET::setTail(EdgeNode* tail) {
	this->tail = tail;
}

void AET::addEdge(EdgeNode* newEdge) {
	/*
	* ��������㷨������������������±ߣ�
	* ��AET�գ�ֱ����ӣ�
	* ���򣬰���xInYMax����˳���ţ�
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

	//�����Ƿ����β7
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

void AET::removeEdge() {
	const GLdouble y = curY;
	//ͷ��ɾ��
	while (head != nullptr && fabs(head->getYMax() - y) < eps) {
		EdgeNode* temp = head;
		head = head->getNext();
		delete temp;
		temp = nullptr;
	}
	//��ɾ����ȫ��tailָ���
	if (head == nullptr) {
		tail = nullptr;
		return;
	}

	for (EdgeNode* pre = head, *cur = head->getNext(); cur != nullptr;) {
		if (fabs(cur->getYMax() - y) < eps) {
			EdgeNode* temp = cur;
			pre->setNext(cur->getNext());
			if (cur == tail) {
				tail = pre;
			}
			cur = cur->getNext();
			delete temp;
			temp = nullptr;
		} else {
			pre = cur;
			cur = cur->getNext();
		}
	}
}

void AET::moveOneStep(ET* edgeTable) {
	//���
	fillLine();
	//ɾ����
	removeEdge();
	
	//ɨ��������
	++curY;
	
	//x=x+1/k
	for (EdgeNode* edge = head; edge != nullptr; edge = edge->getNext()) {
		edge->setX(edge->getX() + edge->getShiftFactor());
	}

	//�ϲ�ET��curY�ı�
	for (BucketNode* bucket = edgeTable->getHead(); bucket != nullptr; bucket = bucket->getNext()) {
		if (fabs(bucket->getY() - curY) < eps) {
			for (EdgeNode* edge = bucket->getHead(); edge != nullptr; edge = edge->getNext()) {
				EdgeNode* newEdge = new EdgeNode(edge);
				addEdge(newEdge);
			}
			break;
		}
	}
}

GLboolean AET::isEmpty() {
	return head == nullptr;
}

void AET::fillLine() {
	bool shouldDraw = true;
	for (EdgeNode* edge = head; edge != nullptr; edge = edge->getNext()) {
		if (shouldDraw) {
			glLineWidth(1);//�����߶ο��
			glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(edge->getX() / 500.0, curY / 350.0);
			glVertex2f(edge->getNext()->getX() / 500.0, curY / 350.0);
			glEnd();
		}
		shouldDraw = !shouldDraw;
	}
}