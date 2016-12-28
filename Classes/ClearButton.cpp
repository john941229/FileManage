#include "ClearButton.h"

void ClearButton::event(cocos2d::Ref* pSender)
{
	ViewSystem* viewSystem = new ViewSystem();
	System* system = new System();
	SystemFile* nowFile = viewSystem->getNowFile();
	SystemFile* fromFile = viewSystem->getFromFile();
	Vector<SystemFile*> fileVec = system->getFileVec();

	nowFile = fileVec.at(0);
	for (auto &e : fileVec)
	{
		if (e->getIsLive())
		{
			e->deleteSelf();
		}
	}

	this->viewLayer->updataView();
}

void ClearButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("clear.png", "clear.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(2);
	menuButton->addChild(clickCatalogButton);
}

ClearButton::ClearButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY)
{
	this->viewLayer = viewLayer;
	createMySelf(menuButton, positionX, positionY);
}

ClearButton::~ClearButton()
{

}