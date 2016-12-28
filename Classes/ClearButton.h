#pragma once
#include <cocos2d.h>
#include "MyButton.h"
#include "System.h"
#include "ViewSystem.h"

USING_NS_CC;
using namespace std;

class ClearButton :
	public MyButton
{
public:
	ClearButton(Menu* menuButton, int positionX, int positionY);
	~ClearButton();
public:
	void event(cocos2d::Ref* pSender);
	void createMySelf(Menu* menuButton, int positionX, int positionY);
};