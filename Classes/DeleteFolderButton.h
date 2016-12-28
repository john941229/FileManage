#pragma once
#include <cocos2d.h>
#include "MyButton.h"
#include "System.h"
#include "ViewSystem.h"
#include "ViewLayer.h"

USING_NS_CC;
using namespace std;

class DeleteFolderButton :
	public MyButton
{
private:
	ViewLayer* viewLayer;
public:
	DeleteFolderButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY);
	~DeleteFolderButton();
public:
	void event(cocos2d::Ref* pSender);
	void createMySelf(Menu* menuButton, int positionX, int positionY);
};