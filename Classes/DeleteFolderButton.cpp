#include "DeleteFolderButton.h"

DeleteFolderButton::DeleteFolderButton(Menu * menuButton, int positionX, int positionY)
{
	createMySelf(menuButton, positionX, positionY);
}

DeleteFolderButton::~DeleteFolderButton()
{
}

void DeleteFolderButton::event(cocos2d::Ref* pSender)
{
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	SystemFile* file = NULL;

	const string catalogName = catalogTTF->getString();
	bool flag = false;
	int num = 0;
	for (auto &e : fileVec)
	{
		if (e->getName()->getCString() == catalogName && e->getIsLive())
		{
			flag = true;
			file = e;
			break;
		}
		num++;
	}

	if (flag)
	{
		file->deleteSelf();
		//updataView();
	}
}

void DeleteFolderButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("delete.png", "delete.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);
}