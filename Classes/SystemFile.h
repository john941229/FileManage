#pragma once
#include "cocos2d.h"
#include "System.h"

USING_NS_CC;
using namespace std;

class SystemFile:
	public Sprite
{
protected:
	// ��system�е�index
	int headIndex;
	// �ļ���
	CCString* name;
	// �Ƿ���Ч
	bool isLive;
	// ��ʵ�ļ�·��
	string path;
	// �Ƿ���ϵͳ�ĸ��ڵ�
	bool isRoot;
	// �ļ�����
	int type;
public:
	SystemFile();
	~SystemFile();
public:
	void setType(int type);
	int getType();
	void setName(CCString* name);
	CCString* getName();
	void setIsLive(bool isLive);
	bool getIsLive();
	void setPath(string fathrePath);
	string getPath();
	void setHeadIndex(int headIndex);
	int getHeadIndex();
	void setIsRoot(bool isRoot);
	bool getIsRoot();
public:
	// ɾ���Լ�
	virtual void deleteSelf();
};

