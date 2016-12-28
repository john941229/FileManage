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
	// �Ƿ���ϵͳ�ĸ��ڵ�
	bool isRoot;
public:
	Folder(System* system, int headIndex, CCString name, string path, bool isRoot);
	Folder();
	~Folder();
public:
	void setIsRoot(bool isRoot);
	bool getIsRoot();
	// ��ӽڵ㵽������
	void addList(int num);
	// ɾ������ļ���
	void deleteSelf();
public:
	static bool createFolder(Folder* father, CCString name);
};