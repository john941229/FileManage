#pragma once
#include <cocos2d.h>
#include "SystemFile.h"

USING_NS_CC;
using namespace std;

class ViewSystem
{
private:
	static Size visibleSize;
	// 现在所处的文件
	static SystemFile* nowFile;
	// 从哪个文件进入的
	static SystemFile* fromFile;
public:
	ViewSystem();
	~ViewSystem();
	Size getVisibleSize();
	SystemFile* getNowFile();
	void setNowFile(SystemFile* nowFile);
	SystemFile* getFromFile();
	void setFromFile(SystemFile* fromFile);
};