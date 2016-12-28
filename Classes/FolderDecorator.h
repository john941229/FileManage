#pragma once
#include <cocos2d.h>
#include "Folder.h"

class FolderDecorator
{
private:
	Folder* folder;
public:
	FolderDecorator(Folder* folder);
	~FolderDecorator();
	// 添加节点到链表中
	void addList(int num);
};