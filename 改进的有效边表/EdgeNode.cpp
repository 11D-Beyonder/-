#include "EdgeNode.h"

EdgeNode::EdgeNode() {
	x = yMax = shiftFactor = 0.0;
	next = nullptr;
}

EdgeNode::EdgeNode(EdgeNode* newEdge) {
	x = newEdge->getX();
	yMax = newEdge->getYMax();
	shiftFactor = newEdge->getShiftFactor();
}

EdgeNode::EdgeNode(GLdouble x, GLdouble yMax, GLdouble shiftFactor) {
	this->x = x;
	this->yMax = yMax;
	this->shiftFactor = shiftFactor;
}

GLdouble EdgeNode::getX() const {
	return x;
}

void EdgeNode::setX(GLdouble xInYMin) {
	this->x = xInYMin;
}

GLdouble EdgeNode::getYMax() const {
	return yMax;
}

void EdgeNode::setYMax(GLdouble yMax) {
	this->yMax = yMax;
}

GLdouble EdgeNode::getShiftFactor() const {
	return shiftFactor;
}

void EdgeNode::setShiftFactor(GLdouble shiftFactor) {
	this->shiftFactor = shiftFactor;
}

EdgeNode* EdgeNode::getNext() const {
	return next;
}

void EdgeNode::setNext(EdgeNode* next) {
	this->next = next;
}

