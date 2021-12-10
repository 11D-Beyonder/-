#pragma once
#include"CPoint.h"
#include<algorithm>
class CLine {
private:
	//保证起点比终点低
	CPoint startPoint;
	CPoint endPoint;
	GLdouble yMin;
	GLdouble yMax;
	GLdouble shiftFactor;

public:

	CLine();
	CLine(CPoint startPoint, CPoint endPoint);
	CLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);

    CPoint getStartPoint() const;

    CPoint getEndPoint() const;

    GLdouble getYMin() const;

    GLdouble getYMax() const;

	/// <summary>
	/// 这条直线的ymax与另一条直线ymin重叠
	/// </summary>
	void shortenYMax();

	/// <summary>
	/// 获取x的步长
	/// </summary>
	/// <returns>斜率的倒数</returns>
	GLdouble getShiftFactor() const;
};