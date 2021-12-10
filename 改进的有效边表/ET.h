#pragma once
#include"BucketNode.h"
class ET {
private:
	BucketNode* head;
	BucketNode* tail;
public:
    /// <summary>
    /// ����ET��
    /// </summary>
    /// <param name="bottom">Ymin</param>
    /// <param name="top">Ymax</param>
    ET(GLint bottom, GLint top);

    BucketNode* getHead() const;
    void setHead(BucketNode* head);

    BucketNode* getTail() const;
    void setTail(BucketNode* tail);

};