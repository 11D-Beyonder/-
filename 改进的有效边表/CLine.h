#pragma once
#include"CPoint.h"
#include<algorithm>
class CLine {
private:
	//��֤�����յ��
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
	/// ����ֱ�ߵ�ymax����һ��ֱ��ymin�ص�
	/// </summary>
	void shortenYMax();

	/// <summary>
	/// ��ȡx�Ĳ���
	/// </summary>
	/// <returns>б�ʵĵ���</returns>
	GLdouble getShiftFactor() const;
};