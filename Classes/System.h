#pragma once
#include <cocos2d.h>
#include "SystemFile.h"
#include "freeMemory.h"
#include "Document.h"
#include "Folder.h"
#include <string>
#include <cstdlib>
#include <iostream> 
#include <io.h> 
#include <sys\stat.h> 
#define _AFXDLL

USING_NS_CC;
using namespace std;

struct linkItem
{
	int num, ne;
};

class System :
	public Sprite
{
private:
	// 系统容积
	int memoryLarge;
	// FTA
	int FTA[1000];
	// 数组模拟链表
	int head[1000];
	linkItem fileArr[1000];
	int fileArrNum;
	// 文件数组
	Vector<SystemFile*> fileVec;
	// 空内容块数组
	Vector<freeMemory*> freeMemoryArr;
	// 第几块内存的起始
	std::map<int, int> fileToVec;
public:
	System();
	~System();
public:
	int* getHead();
	Vector<SystemFile*> getFileVec();
	Vector<freeMemory*> getFreeMemoryArr();
	linkItem* getFileArr();
	int getFileArrNum();
	std::map<int, int> getFileToVec();
public:
	bool reduceMemoryLarge(int size);
};

