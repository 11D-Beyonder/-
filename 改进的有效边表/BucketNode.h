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
	/// 在桶中装入yMin=y的边
	/// </summary>
	/// <param name="newEdge">新的边</param>
	void addEdge(EdgeNode* newEdge);
};