#pragma once
#include <cocos2d.h>
#include "File.h"
#include "freeMemory.h"
#include "FileShow.h"
#include <map>
#include <cstdlib>
#include <iostream> 
#include <io.h> 
#include <sys\stat.h> 
#define _AFXDLL

USING_NS_CC;
using namespace std;
const int memory = 1000000;

struct da
{
	int num, ne;
};

class ViewLayer:
	public Layer
{
private:
	File* fromfile;
	File* newfile;
	int FTA[1000];
	int head[1000];
	da fileArr[1000];
	int fileArrNum;
	int memoryLarge;
	float posX, posY;
public:
	Vector<File*> fileVec;
	Vector<freeMemory*> freeMemoryArr;
	std::map<int, int> fileToVec;
	Vector<Sprite*> filePicVec;
	Vector<TextFieldTTF*> fileWordVec;
	Menu* menuButton;
	TextFieldTTF *catalogTTF;
	TextFieldTTF *fileTTF;
	TextFieldTTF *showPath;
	TextFieldTTF *showMemory;
	int count;

	ViewLayer();
	~ViewLayer();
	bool addFile(CCString name);
	bool addCatalog(CCString name);
	bool checkName(CCString name);
	void deleteCatalog(int num);
	void deleteFile(int num);
	void addList(int num);
	int findAdress(int size);
public:
	Size visibleSize;
	static ViewLayer* create();
	virtual bool init();
	void initUI();
	void addFunctionButton();
public:
	void updataView();
	void clickFile(cocos2d::Ref* pSender);
	void clickCatalog(cocos2d::Ref* pSender);
	void addFileButton(cocos2d::Ref* pSender);
	void addCatalogButton(cocos2d::Ref* pSender);
	void deleteFileButton(cocos2d::Ref* pSender);
	void deleteCatalogButton(cocos2d::Ref* pSender);
	void backOffButton(cocos2d::Ref* pSender);
	void clearBtton(cocos2d::Ref* pSender);
	void addListener();
};

