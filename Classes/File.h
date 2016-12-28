#pragma once
#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class File:
	public Sprite
{
/*
	type = 0ΪĿ¼ type = 1Ϊ�ļ�
	Ŀ¼û�д�С 
	�ļ��д�С
*/
private:
	CCString name;
	int type;
	int adress;
	int memoryLong;
	bool isLive;
	int num;
	string path;
	bool isRoot;
public:
	File(CCString name,int type, int adress, int memoryLong);
	File();
	~File();
public:
	void setName(CCString name);
	CCString getName();
	void setType(int type);
	int getType();
	void setAdress(int adress);
	int getAdress();
	void setMemoryLong(int memoryLong);
	int getMemoryLong();
	void setIsLive(bool isLive);
	bool getIsLive();
	CCString getFile();
	void setNum(int num);
	int getNum();
	void setPath(string fathrePath);
	string getPath();
	void setIsRoot(bool isRoot);
	bool getIsRoot();
};

