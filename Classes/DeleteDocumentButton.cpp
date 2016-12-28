#include "DeleteDocumentButton.h"

void DeleteDocumentButton::event(cocos2d::Ref* pSender)
{
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	std::map<int, int> fileToVec = system->getFileToVec();
	Vector<freeMemory*> freeMemoryArr = system->getFreeMemoryArr();

	bool flag = false;
	const string fileName = fileTTF->getString();
	SystemFile* file = NULL;
	
	int num = 0;
	for (auto &e : fileVec)
	{
		if (e->getName()->getCString() == fileName && e->getIsLive())
		{
			flag = true;
			file = e;
			break;
		}
		num++;
	}

	if (flag)
	{
		system->addMemoryLarge(freeMemoryArr.at(file->getHeadIndex())->getLong());
		file->deleteSelf();
		//updataView();
	}
}

void DeleteDocumentButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("delete.png", "delete.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);
}

DeleteDocumentButton::DeleteDocumentButton(Menu* menuButton, int positionX, int positionY)
{
	createMySelf(menuButton, positionX, positionY);
}

DeleteDocumentButton::~DeleteDocumentButton()
{

}