#pragma once
#include <cocos2d.h>
#include "SystemFile.h"
#include "SystemFileDecorator.h"
#include "FolderDecorator.h"
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
public:
	Folder(int headIndex, CCString* name, string path, bool isRoot);
	Folder();
	~Folder();
public:
	// 删除这个文件夹
	void deleteSelf();
public:
	static bool createFolder(Folder* father, CCString* name);
};