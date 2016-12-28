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
	// �ڴ濪ʼ��ַ
	int adress;
	// ��ռ�ڴ�����
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
	// ɾ������ļ�
	void deleteSelf();
public:
	// �����ļ���
	static bool create(Folder* father, CCString* name);
};

