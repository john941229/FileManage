#include "BackOffButton.h"

void BackOffButton::event(cocos2d::Ref* pSender)
{
	ViewSystem* viewSystem = new ViewSystem();
	SystemFile* nowFile = viewSystem->getNowFile();
	SystemFile* fromFile = viewSystem->getFromFile();

	if (!nowFile->getIsRoot())
	{
		nowFile = fromFile;
		//updataView();
	}
	else
	{
		CCLOG("it is root,can't back off");
	}
}

void BackOffButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("backOff.png", "backOff.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(2);
	menuButton->addChild(clickCatalogButton);
}

BackOffButton::BackOffButton(Menu* menuButton, int positionX, int positionY)
{
	createMySelf(menuButton, positionX, positionY);
}

BackOffButton::~BackOffButton()
{

}