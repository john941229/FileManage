#include "EnterFolderButton.h"

EnterFolderButton::EnterFolderButton(ViewLayer* viewLayer, Menu * menuButton, int positionX, int positionY)
{
	this->viewLayer = viewLayer;
	createMySelf(menuButton, positionX, positionY);
}

EnterFolderButton::~EnterFolderButton()
{
}

void EnterFolderButton::event(cocos2d::Ref* pSender)
{
	ViewSystem* viewSystem = new ViewSystem();
	System* system = new System();
	SystemFile* nowFile = viewSystem->getNowFile();
	SystemFile* fromFile = viewSystem->getFromFile();
	Vector<SystemFile*> fileVec = system->getFileVec();

	bool flag = false;
	SystemFile* oldFile = fromFile;
	fromFile = nowFile;
	for (auto &e : fileVec)
	{
		if (e->getName()->getCString() == this->viewLayer->catalogTTF->getString())
		{
			nowFile = e;
			flag = true;
			break;
		}
	}
	if (flag)
	{
		this->viewLayer->updataView();
	}
	else
	{
		fromFile = oldFile;
	}
}

void EnterFolderButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("clickTo.png", "clickTo.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);
}