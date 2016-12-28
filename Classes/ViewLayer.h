#pragma once
#include <cocos2d.h>
#include "File.h"
#include "freeMemory.h"
#include "FileShow.h"
#include "ButtonFactory.h"
#include "FileFactory.h"
#include <map>
#include <cstdlib>
#include <iostream> 
#include <io.h> 
#include <sys\stat.h>
#define _AFXDLL

USING_NS_CC;
using namespace std;

class ViewLayer:
	public Layer
{
private:
	float posX, posY;
public:
	Menu* menuButton;
	Vector<Sprite*> filePicVec;
	Vector<TextFieldTTF*> fileWordVec;
	TextFieldTTF *catalogTTF;
	TextFieldTTF *fileTTF;
	TextFieldTTF *showPath;
	TextFieldTTF *showMemory;
	int count;

	ViewLayer();
	~ViewLayer();
public:
	static ViewLayer* create();
	virtual bool init();
	void initUI();
	void addFunctionButton();
	void updataView();
	void addListener();
};

