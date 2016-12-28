#include "CreateDocumentButton.h"

void CreateDocumentButton::event(cocos2d::Ref* pSender)
{
	const string fileN = this->viewLayer->fileTTF->getString();
	CCString* fileName = CCString::create(fileN);
	ViewSystem* viewSystem = new ViewSystem();
	Document* document = new Document();
	Folder* fromFolder = (Folder*)viewSystem->getFromFile();

	if (document->create(fromFolder, fileName))
	{
		//CCLOG("success");
		this->viewLayer->updataView();
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

CreateDocumentButton::CreateDocumentButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY)
{
	this->viewLayer = viewLayer;
	createMySelf(menuButton, positionX, positionY);
}

CreateDocumentButton::~CreateDocumentButton()
{

}