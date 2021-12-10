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
	* 设计增量算法，在有序链表中填充新边；
	* 若AET空，直接添加；
	* 否则，按照xInYMax递增顺序存放；
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

	//检验是否插入尾7
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

void AET::removeEdge() {
	const GLdouble y = curY;
	//头部删除
	while (head != nullptr && fabs(head->getYMax() - y) < eps) {
		EdgeNode* temp = head;
		head = head->getNext();
		delete temp;
		temp = nullptr;
	}
	//若删除完全，tail指向空
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
	//填充
	fillLine();
	//删除边
	removeEdge();
	
	//扫描线上移
	++curY;
	
	//x=x+1/k
	for (EdgeNode* edge = head; edge != nullptr; edge = edge->getNext()) {
		edge->setX(edge->getX() + edge->getShiftFactor());
	}

	//合并ET中curY的边
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
			glLineWidth(1);//设置线段宽度
			glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(edge->getX() / 500.0, curY / 350.0);
			glVertex2f(edge->getNext()->getX() / 500.0, curY / 350.0);
			glEnd();
		}
		shouldDraw = !shouldDraw;
	}
}