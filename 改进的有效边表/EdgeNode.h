#pragma once
#include<GLFW/glfw3.h>
class EdgeNode {
private:
	GLdouble x;
	GLdouble yMax;
	GLdouble shiftFactor;
	EdgeNode* next;
public:
    EdgeNode(EdgeNode* newEdge);
    EdgeNode();
    EdgeNode(GLdouble x, GLdouble yMax, GLdouble shiftFactor);

    GLdouble getX() const;
    void setX(GLdouble xInYMin);

    GLdouble getYMax() const;
    void setYMax(GLdouble yMax);

    GLdouble getShiftFactor() const;
    void setShiftFactor(GLdouble shiftFactor);

    EdgeNode* getNext() const;
    void setNext(EdgeNode* next);
};