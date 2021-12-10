#pragma once
#include "EdgeNode.h"
#include<cmath>
class BucketNode {
private:
	const GLdouble eps = 1e-7;
	GLdouble y;
	EdgeNode* head;
	EdgeNode* tail;
	BucketNode* next;
public:
	BucketNode(const GLdouble& y);

	GLint getY() const;
	void setY(GLint y);

	EdgeNode* getHead() const;
	void setHead(EdgeNode* head);

	BucketNode* getNext() const;
	void setNext(BucketNode* next);

	/// <summary>
	/// ��Ͱ��װ��yMin=y�ı�
	/// </summary>
	/// <param name="newEdge">�µı�</param>
	void addEdge(EdgeNode* newEdge);
};