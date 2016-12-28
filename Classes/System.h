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
	// ϵͳ�ݻ�
	int memoryLarge;
	// FTA
	int FTA[1000];
	// ����ģ������
	int head[1000];
	linkItem fileArr[1000];
	int fileArrNum;
	// �ļ�����
	Vector<SystemFile*> fileVec;
	// �����ݿ�����
	Vector<freeMemory*> freeMemoryArr;
	// �ڼ����ڴ����ʼ
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

