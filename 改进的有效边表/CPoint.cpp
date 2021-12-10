#include "CPoint.h"

GLdouble CPoint::getX() const {
	return x;
}

void CPoint::setX(GLdouble x) {
	this->x = x;
}

GLdouble CPoint::getY() const {
	return y;
}

void CPoint::setY(GLdouble y) {
	this->y = y;
}

CPoint::CPoint() {
	x = y = 0.0;
}

CPoint::CPoint(GLdouble x, GLdouble y) {
	this->x = x;
	this->y = y;
}

bool CPoint::operator==(const CPoint& other) const {
	const GLdouble eps = 1e-7;
	return fabs(x - other.getX()) < eps && fabs(y - other.getY()) < eps;
}

bool CPoint::operator<(const CPoint& other) const {
	const GLdouble eps = 1e-7;
	GLdouble t1 = atan2(y, x);
	GLdouble t2 = atan2(other.getY(), other.getX());
	if (fabs(t1 - t2) < eps) {
		return x < other.getX();
	} else {
		return t1 < t2;
	}
}