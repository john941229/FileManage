#pragma once
#include <cocos2d.h>
#include "System.h"

USING_NS_CC;
using namespace std;

class MyButton :
	public MenuItemImage
{
public:
	virtual void event(cocos2d::Ref* pSender);
	virtual void createMySelf(Menu* menuButton, int positionX, int positionY);
};
