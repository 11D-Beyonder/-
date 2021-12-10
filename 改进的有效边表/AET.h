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
	/// ɨ���������ƶ�һ����
	/// ȡ��yMAX=curY�ı�
	/// �ϲ�ET��curY�еı�
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
	/// ��ɨ������y�߶�ʱ��ȥ��yMax=y�ıߡ�
	/// </summary>
	/// <param name="y">ɨ���ߵ�����</param>
	void removeEdge();

	/// <summary>
	/// ���һ����
	/// </summary>
	/// <param name="newEdge">�±ߵ���Ϣ</param>
	void addEdge(EdgeNode* newEdge);
	/// <summary>
	/// ��һ��ֱ��
	/// </summary>
	void fillLine();
};