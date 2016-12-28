#pragma once
#include "cocos2d.h"
#include "System.h"

USING_NS_CC;
using namespace std;

class SystemFile:
	public Sprite
{
protected:
	// 在system中的index
	int headIndex;
	// 文件名
	CCString* name;
	// 是否有效
	bool isLive;
	// 真实文件路径
	string path;
	// 是否是系统的根节点
	bool isRoot;
	// 文件类型
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
	// 删除自己
	virtual void deleteSelf();
};

