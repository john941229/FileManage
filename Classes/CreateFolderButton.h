#pragma once
#include <cocos2d.h>
#include "MyButton.h"
#include "System.h"
#include "ViewSystem.h"
#include "Folder.h"
#include "ViewLayer.h"

USING_NS_CC;
using namespace std;

class CreateFolderButton :
	public MyButton
{
private:
	ViewLayer* viewLayer;
public:
	CreateFolderButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY);
	~CreateFolderButton();
public:
	void event(cocos2d::Ref* pSender);
	void createMySelf(Menu* menuButton, int positionX, int positionY);
};