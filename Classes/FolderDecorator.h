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
	// ��ӽڵ㵽������
	void addList(int num);
};