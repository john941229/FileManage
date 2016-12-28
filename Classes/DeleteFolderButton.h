#pragma once
#include <cocos2d.h>
#include "MyButton.h"
#include "System.h"
#include "ViewSystem.h"

USING_NS_CC;
using namespace std;

class DeleteFolderButton :
	public MyButton
{
public:
	DeleteFolderButton(Menu* menuButton, int positionX, int positionY);
	~DeleteFolderButton();
public:
	void event(cocos2d::Ref* pSender);
	void createMySelf(Menu* menuButton, int positionX, int positionY);
};