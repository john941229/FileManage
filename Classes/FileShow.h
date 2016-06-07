#pragma once
#include "C:\MyCocos\FileManage\cocos2d\cocos\2d\CCSprite.h"
#include <cocos2d.h>
#include <iostream>

using namespace std;
USING_NS_CC;

class FileShow :
	public Layer
{
private:
	int fromNum;
	CCString filePath;
	int adress;
	int memoryLong;
public:
	Menu * menu;
	Size visiblesize;
	TextFieldTTF *ttf;
	TextFieldTTF *information;
	virtual bool init();
	CREATE_FUNC(FileShow);
	FileShow();
	FileShow(CCString filePath,int adress,int memoryLong);
	~FileShow();
	void setFromNum(int num);
public:
	void loadFileButton(Ref* Spender);
	void backOffButton(Ref* Spender);
	void addListener();
};

