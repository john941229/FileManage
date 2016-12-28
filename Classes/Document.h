#pragma once
#include <cocos2d.h>
#include "SystemFile.h"
#include "System.h"
#include "Folder.h"
#include "SystemFileDecorator.h"
#include <string>
#include <cstdlib>
#include <iostream> 
#include <io.h> 
#include <sys\stat.h> 
#define _AFXDLL

USING_NS_CC;
using namespace std;

class Document :
	public SystemFile
{
private:
	// 内存开始地址
	int adress;
	// 所占内存容量
	int memoryLong;
public:
	Document();
	Document(int headIndex, CCString* name, string path, int adress, int memoryLong);
	~Document();
public:
	void setAdress(int adress);
	int getAdress();
	void setMemoryLong(int memoryLong);
	int getMemoryLong();
	// 删除这个文件
	void deleteSelf();
public:
	// 创建文件夹
	static bool create(Folder* father, CCString* name);
};

