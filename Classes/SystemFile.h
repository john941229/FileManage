#pragma once
#include "cocos2d.h"
#include "System.h"

USING_NS_CC;
using namespace std;

class SystemFile:
	public Sprite
{
protected:
	// 文件处于的系统
	System* system;
	// 在system中的index
	int headIndex;
	// 文件名
	CCString name;
	// 是否有效
	bool isLive;
	// 真实文件路径
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
	// 检查name是否是儿子节点的名字(不允许一个儿子节点下同名)
	bool checkName(CCString name);
	// 寻找系统中的内存最适空闲位置
	int findAdress(int size);
	virtual void deleteSelf();
};

