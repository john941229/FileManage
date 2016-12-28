#include "CreateDocumentButton.h"

void CreateDocumentButton::event(cocos2d::Ref* pSender)
{
	const string fileN = fileTTF->getString();
	CCString* fileName = CCString::create(fileN);
	ViewSystem* viewSystem = new ViewSystem();
	Document* document = new Document();
	Folder* fromFolder = (Folder*)viewSystem->getFromFile();

	if (document->create(fromFolder, fileName))
	{
		//CCLOG("success");
		//updataView();
	}
}

void CreateDocumentButton::createMySelf(Menu* menuButton, int positionX, int positionY)
{
	auto clickCatalogButton = MenuItemImage::create("addButton.png", "addButton.png",
		CC_CALLBACK_1(this->event, this));
	clickCatalogButton->setPosition(positionX, positionY);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);
}

CreateDocumentButton::CreateDocumentButton(Menu* menuButton, int positionX, int positionY)
{
	createMySelf(menuButton, positionX, positionY);
}

CreateDocumentButton::~CreateDocumentButton()
{

}