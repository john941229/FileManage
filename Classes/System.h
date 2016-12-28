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

// ȫ����
class System
{
private:
	// ϵͳ�ݻ�
	static int memoryLarge;
	// FTA
	static int FTA[1000];
	// �ļ�����
	static Vector<SystemFile*> fileVec;
	// �����ݿ�����
	static Vector<freeMemory*> freeMemoryArr;
	// �ڼ����ڴ����ʼ
	static std::map<int, int> fileToVec;
	// ����ģ������
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

