#pragma once
#include <cocos2d.h>
#include "SystemFile.h"
#include <string>
#include <cstdlib>
#include <iostream> 
#include <io.h> 
#include <sys\stat.h> 
#define _AFXDLL

USING_NS_CC;
using namespace std;

class Folder :
	public SystemFile
{
private:
	// 是否是系统的根节点
	bool isRoot;
public:
	Folder(System* system, int headIndex, CCString name, string path, bool isRoot);
	Folder();
	~Folder();
public:
	void setIsRoot(bool isRoot);
	bool getIsRoot();
	// 添加节点到链表中
	void addList(int num);
	// 删除这个文件夹
	void deleteSelf();
public:
	static bool createFolder(Folder* father, CCString name);
};