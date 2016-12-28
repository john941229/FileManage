#pragma once
#include <cocos2d.h>
#include "MyButton.h"
#include "ViewSystem.h"
#include "FileShow.h"
#include "ViewLayer.h"

USING_NS_CC;
using namespace std;

class EnterDocumentButton:
	public MyButton
{
private:
	ViewLayer* viewLayer;
public:
	EnterDocumentButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY);
	~EnterDocumentButton();
public:
	void event(cocos2d::Ref* pSender);
	void createMySelf(Menu* menuButton, int positionX, int positionY);
};