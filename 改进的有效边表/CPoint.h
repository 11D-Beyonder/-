#pragma once
#include<GLFW/glfw3.h>
#include<cmath>
class CPoint {
private:
	GLdouble x;
	GLdouble y;
public:
    CPoint();
    CPoint(GLdouble x, GLdouble y);

    GLdouble getX() const;
    void setX(GLdouble x);

    GLdouble getY() const;
    void setY(GLdouble y);

    bool operator==(const CPoint& other) const;
    
    /// <summary>
    /// ÓÃÓÚ¼«½ÇÅÅÐò
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    bool operator<(const CPoint& other) const;
};