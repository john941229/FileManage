#include "CreateFolderButton.h"

void CreateFolderButton::event(cocos2d::Ref* pSender)
{
	const string folderStr = catalogTTF->getString();
	CCString* folderName = CCString::create(folderStr);
	ViewSystem* viewSystem = new ViewSystem();
	Folder* folder = new Folder();
	Folder* fromFolder = (Folder*) viewSystem->getFromFile();

	if (folder->createFolder(fromFolder, folderName))
	{
		//CCLOG("success");
		//updataView();
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

CreateFolderButton::CreateFolderButton(Menu* menuButton, int positionX, int positionY)
{
	createMySelf(menuButton, positionX, positionY);
}

CreateFolderButton::~CreateFolderButton()
{

}