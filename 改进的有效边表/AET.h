#pragma once
#include"EdgeNode.h"
#include"ET.h"
#include<cmath>
class AET {
public:
	
	AET();
	AET(BucketNode* bucket);
	~AET();
	/// <summary>
	/// 扫描线向上移动一步，
	/// 取出yMAX=curY的边
	/// 合并ET中curY中的边
	/// </summary>
	void moveOneStep(ET* edgeTable);

	EdgeNode* getHead() const;
	void setHead(EdgeNode* head);

	EdgeNode* getTail() const;
	void setTail(EdgeNode* tail);

	GLboolean isEmpty();
private:
	GLdouble curY;
	EdgeNode* head;
	EdgeNode* tail;
	const GLdouble eps = 1e-7;
private:
	/// <summary>
	/// 当扫描线在y高度时，去掉yMax=y的边。
	/// </summary>
	/// <param name="y">扫描线的坐标</param>
	void removeEdge();

	/// <summary>
	/// 添加一条边
	/// </summary>
	/// <param name="newEdge">新边的信息</param>
	void addEdge(EdgeNode* newEdge);
	/// <summary>
	/// 画一条直线
	/// </summary>
	void fillLine();
};