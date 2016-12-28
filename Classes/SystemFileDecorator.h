#pragma once
#include <cocos2d.h>
#include "SystemFile.h"

class SystemFileDecorator
{
private:
	SystemFile* systemFile;
public:
	SystemFileDecorator(SystemFile* systemFile);
	~SystemFileDecorator();
	// 检查name是否是儿子节点的名字(不允许一个儿子节点下同名)
	bool checkName(CCString* name);
	// 寻找系统中的内存最适空闲位置
	int findAdress(int size);
};