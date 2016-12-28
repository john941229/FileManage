#pragma once
#include <cocos2d.h>
#include "SystemFile.h"
#include "freeMemory.h"
#include "Document.h"
#include "Folder.h"
#include "FileTree.h"
#include <string>
#include <cstdlib>
#include <iostream> 
#include <io.h> 
#include <sys\stat.h> 
#define _AFXDLL

USING_NS_CC;
using namespace std;

// 全局类
class System
{
private:
	// 系统容积
	static int memoryLarge;
	// FTA
	static int FTA[1000];
	// 文件数组
	static Vector<SystemFile*> fileVec;
	// 空内容块数组
	static Vector<freeMemory*> freeMemoryArr;
	// 第几块内存的起始
	static std::map<int, int> fileToVec;
	// 数组模拟链表
	static FileTree* fileTree;
public:
	System();
	~System();
public:
	int getMemoryLarge();
	void setFileVec(Vector<SystemFile*> fileVec);
	Vector<SystemFile*> getFileVec();
	void setFreeMemoryArr(Vector<freeMemory*> freeMemoryArr);
	Vector<freeMemory*> getFreeMemoryArr();
	void setFileToVec(std::map<int, int> fileToVec);
	std::map<int, int> getFileToVec();
	FileTree* getFileTree();
public:
	static void createMySelf();
	bool reduceMemoryLarge(int size);
	void addMemoryLarge(int size);
};

