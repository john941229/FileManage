#pragma once
#include <cocos2d.h>
#include "System.h"

USING_NS_CC;
using namespace std;

struct linkItem
{
	int num, ne;
};

class FileTree
{
public:
	int head[1000];
	linkItem fileArr[1000];
	int fileArrNum;
	FileTree();
	~FileTree();
public:
	// 添加节点到文件树中
	int addList(int fatherIndex, int headIndex);
	// 删除子树
	void deleteSonTree(int headIndex);
};