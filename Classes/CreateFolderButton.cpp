#include "CreateFolderButton.h"

void CreateFolderButton::event(cocos2d::Ref* pSender)
{
	const string folderStr = this->viewLayer->catalogTTF->getString();
	CCString* folderName = CCString::create(folderStr);
	ViewSystem* viewSystem = new ViewSystem();
	Folder* folder = new Folder();
	Folder* fromFolder = (Folder*) viewSystem->getFromFile();

	if (folder->createFolder(fromFolder, folderName))
	{
		//CCLOG("success");
		this->viewLayer->updataView();
	}
}

void CreateFolderButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("addButton.png", "addButton.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);
}

CreateFolderButton::CreateFolderButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY)
{
	this->viewLayer = viewLayer;
	createMySelf(menuButton, positionX, positionY);
}

CreateFolderButton::~CreateFolderButton()
{

}