#include "EnterDocumentButton.h"

EnterDocumentButton::EnterDocumentButton(ViewLayer* viewLayer, Menu * menuButton, int positionX, int positionY)
{
	this->viewLayer = viewLayer,
	createMySelf(menuButton, positionX, positionY);
}

EnterDocumentButton::~EnterDocumentButton()
{
}

void EnterDocumentButton::event(cocos2d::Ref* pSender)
{
	ViewSystem* viewSystem = new ViewSystem();
	System* system = new System();
	SystemFile* nowFile = viewSystem->getNowFile();
	SystemFile* fromFile = viewSystem->getFromFile();
	Vector<SystemFile*> fileVec = system->getFileVec();
	Vector<freeMemory*> freeMemoryArr = system->getFreeMemoryArr();
	std::map<int, int> fileToVec = system->getFileToVec();

	bool flag = false;
	for (auto &e : fileVec)
	{
		if (e->getName()->getCString() == this->viewLayer->fileTTF->getString())
		{
			nowFile = e;
			flag = true;
			break;
		}
	}

	int position = fileToVec[nowFile->getHeadIndex()];

	if (flag)
	{
		FileShow * fileshow = new FileShow(nowFile->getPath(), freeMemoryArr.at(position)->getStart(), freeMemoryArr.at(position)->getLong());
		fileshow->setFromNum(nowFile->getHeadIndex());
		Director::getInstance()->getRunningScene()->addChild(fileshow);
	}
	this->viewLayer->updataView();
}

void EnterDocumentButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("clickTo.png", "clickTo.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);
}