#pragma once
#include "cocos2d.h"
#include "System.h"

USING_NS_CC;
using namespace std;

class SystemFile:
	public Sprite
{
protected:
	// �ļ����ڵ�ϵͳ
	System* system;
	// ��system�е�index
	int headIndex;
	// �ļ���
	CCString name;
	// �Ƿ���Ч
	bool isLive;
	// ��ʵ�ļ�·��
	string path;
public:
	SystemFile();
	~SystemFile();
public:
	void setName(CCString name);
	CCString getName();
	void setIsLive(bool isLive);
	bool getIsLive();
	void setPath(string fathrePath);
	string getPath();
	void setSystem(System* system);
	System* getSystem();
	void setHeadIndex(int headIndex);
	int getHeadIndex();
	void setFileVecIndex(int fileVecIndex);
	int getFileVecIndex();
public:
	// ���name�Ƿ��Ƕ��ӽڵ������(������һ�����ӽڵ���ͬ��)
	bool checkName(CCString name);
	// Ѱ��ϵͳ�е��ڴ����ʿ���λ��
	int findAdress(int size);
	virtual void deleteSelf();
};

