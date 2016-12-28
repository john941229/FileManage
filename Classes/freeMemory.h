#pragma once
#include "C:\fileManage\FileManage\cocos2d\cocos\2d\CCNode.h"
#include <cocos2d.h>

USING_NS_CC;

class freeMemory :
	public Node
{
private:
	// 起始位置
	int _start;
	// 长度
	int _long;
	// 类型(0 是空的，2 是被合并了的)
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

