#pragma once
#include "C:\fileManage\FileManage\cocos2d\cocos\2d\CCNode.h"
#include <cocos2d.h>

USING_NS_CC;

class freeMemory :
	public Node
{
private:
	// ��ʼλ��
	int _start;
	// ����
	int _long;
	// ����(0 �ǿյģ�2 �Ǳ��ϲ��˵�)
	int _type;
public:
	int getLong();
	int getStart();
	int getType();
	void setStart(int start);
	void setLong(int l);
	void setType(int type);
	freeMemory(int start, int l, int type);
	freeMemory();
	~freeMemory();
};

