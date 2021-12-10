#include "CLine.h"

CPoint CLine::getStartPoint() const {
	return startPoint;
}

CPoint CLine::getEndPoint() const {
	return endPoint;
}

GLdouble CLine::getYMin() const {
	return yMin;
}

GLdouble CLine::getYMax() const {
	return yMax;
}

void CLine::shortenYMax() {
	--yMax;
	endPoint.setY(yMax);
	endPoint.setX(endPoint.getX() - shiftFactor);
}

GLdouble CLine::getShiftFactor() const {
	return shiftFactor;
}

CLine::CLine() {
	startPoint = CPoint(0, 0);
	endPoint = CPoint(0, 0);
	yMax = yMin = 0;
}

CLine::CLine(CPoint startPoint, CPoint endPoint) {
	if (startPoint.getY() > endPoint.getY()) {
		this->startPoint = endPoint;
		this->endPoint = startPoint;
	} else {
		this->startPoint = startPoint;
		this->endPoint = endPoint;
	}
	this->yMin = this->startPoint.getY();
	this->yMax = this->endPoint.getY();
	this->shiftFactor=(this->startPoint.getX() - this->endPoint.getX()) / (this->startPoint.getY() - this->endPoint.getY());
}

CLine::CLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	CPoint startPoint = CPoint(x1, y1);
	CPoint endPoint = CPoint(x2, y2);
	if (startPoint.getY() > endPoint.getY()) {
		this->startPoint = endPoint;
		this->endPoint = startPoint;
	} else {
		this->startPoint = startPoint;
		this->endPoint = endPoint;
	}
	this->yMin = std::min(y1, y2);
	this->yMax = std::max(y1, y2);
	this->shiftFactor=(this->startPoint.getX() - this->endPoint.getX()) / (this->startPoint.getY() - this->endPoint.getY());
}