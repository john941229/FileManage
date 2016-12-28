#include "ViewLayer.h"

ViewLayer::ViewLayer()
{
	init();
}

ViewLayer::~ViewLayer()
{
}

ViewLayer* ViewLayer::create()
{
	ViewLayer *viewlayer = new ViewLayer();
	if (viewlayer)
	{
		viewlayer->autorelease();
		return viewlayer;
	}
	CC_SAFE_DELETE(viewlayer);
	return nullptr;
}

void ViewLayer::addFunctionButton()
{
	ViewSystem* viewSystem = new ViewSystem();
	catalogTTF = new TextFieldTTF();
	fileTTF = new TextFieldTTF();
	catalogTTF->setString("Entry the name of catalog!");
	catalogTTF->setSystemFontSize(20);
	catalogTTF->setPosition(viewSystem->visibleSize.width / 2 - 60, 50);
	addChild(catalogTTF);
	fileTTF->setString("Entry the name of file!");
	fileTTF->setSystemFontSize(20);
	fileTTF->setPosition(viewSystem->visibleSize.width / 2 - 60, 100);
	addChild(fileTTF);
	addListener();

	// 使用按钮工厂生产所有的按钮
	ButtonFactory* buttonFactory = new ButtonFactory();

	auto backOffButton = buttonFactory->createButton(0, this, menuButton, 42, -120);
	auto clearButton = buttonFactory->createButton(1, this, menuButton, 215, 100);
	auto createDocumentButton = buttonFactory->createButton(2, this, menuButton, 75, 50);
	auto createFolderButton = buttonFactory->createButton(3, this, menuButton, 75, 100);
	auto deleteFolderButton = buttonFactory->createButton(4, this, menuButton, 155, 50);
	auto deleteDocumentButton = buttonFactory->createButton(5, this, menuButton, 155, 100);
	auto enterFolderButton = buttonFactory->createButton(6, this, menuButton, 115, 50);
	auto enterDocumentButton = buttonFactory->createButton(7, this, menuButton, 115, 100);
}

bool ViewLayer::init()
{
	System* system = new System();
	system->createMySelf();
}

void ViewLayer::initUI()
{
	System* system = new System();
	ViewSystem* viewSystem = new ViewSystem();

	//添加背景
	Sprite * backGround = Sprite::create("backGroundN.png");
	Size size = Director::getInstance()->getWinSize();
	backGround->setPosition(size.width / 2, size.height / 2);
	float spx = backGround->getTextureRect().getMaxX();
	float spy = backGround->getTextureRect().getMaxY();
	backGround->setScaleX(size.width / spx);
	backGround->setScaleY(size.height / spy);
	addChild(backGround);

	showPath = new TextFieldTTF();
	showPath->setString("c:\\workRoom");
	showPath->setSystemFontSize(20);
	showPath->setTextColor(Color4B::BLACK);
	showPath->setAnchorPoint(Vec2::ZERO);
	showPath->setPosition(240, viewSystem->visibleSize.height - 130);
	addChild(showPath);

	showMemory = new TextFieldTTF();
	char info[100];
	sprintf(info, "Additional Memory: %d KB", system->getMemoryLarge());
	showMemory->setString(info);
	showMemory->setSystemFontSize(30);
	showMemory->setTextColor(Color4B::BLACK);
	showMemory->setPosition(viewSystem->visibleSize.width / 2, viewSystem->visibleSize.height - 30);
	addChild(showMemory);

	menuButton = Menu::create(NULL);
	menuButton->setPosition(Vec2::ZERO);
	addChild(menuButton);
	addFunctionButton();
}

void ViewLayer::updataView()
{
	ViewSystem* viewSystem = new ViewSystem();
	System* system = new System();
	SystemFile* nowFile = viewSystem->getNowFile();
	Vector<SystemFile*> fileVec = system->getFileVec();


	showPath->setString(nowFile->getPath());
	char info[100];
	sprintf(info, "Additional Memory: %d KB", system->getMemoryLarge());
	showMemory->setString(info);
	//清除掉之前的内容
	for (auto &e : filePicVec)
	{
		e->setVisible(false);
		removeChild(e);
	}

	for (auto &e : fileWordVec)
	{
		e->setVisible(false);
		removeChild(e);
	}

	fileWordVec.clear();
	filePicVec.clear();
	count = 1;
	posX = viewSystem->visibleSize.width / 2 - 190;
	posY = viewSystem->visibleSize.height / 2 + 185;

	//将所有要显示的文件、目录添加到vector中
	int num = nowFile->getHeadIndex();
	int p = system->getFileTree()->head[num];
	while (p != 0)
	{
		if (fileVec.at(system->getFileTree()->fileArr[p].num)->getIsLive())
		{
			Sprite *sp;
			TextFieldTTF *spName = new TextFieldTTF();
			if (fileVec.at(system->getFileTree()->fileArr[p].num)->getType() == 0)
			{
				sp = Sprite::create("catalog.png");
				spName->setString(fileVec.at(system->getFileTree()->fileArr[p].num)->getName()->getCString());
			}
			else
			{
				sp = Sprite::create("fileN.png");
				string filename = fileVec.at(system->getFileTree()->fileArr[p].num)->getName()->getCString();
				filename = filename + ".txt";
				spName->setString(filename);
				sp->setScale(2);
			}

			filePicVec.pushBack(sp);
			fileWordVec.pushBack(spName);
			spName->setTextColor(Color4B::WHITE);
			spName->setSystemFontSize(18);

			//计算位置
			sp->setPosition(posX, posY);
			spName->setPosition(posX, posY - 40);
			addChild(sp);
			addChild(spName);
			count++;
			posX += 75;
			if (count > 8)
			{
				posX = viewSystem->visibleSize.width / 2 - 190;
				posY -= 75;
				count = count - 11;
			}
		}
		p = system->getFileTree()->fileArr[p].ne;
	}
}

void ViewLayer::addListener()
{
	auto director = Director::getInstance();
	auto handler = [=](Touch* t, Event* e)
	{
		auto target = e->getCurrentTarget();
		if (target->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (catalogTTF == target)
			{
				catalogTTF->attachWithIME();
			}
			else if (fileTTF == target)
			{
				fileTTF->attachWithIME();
			}
		}
		return false;
	};

	auto catalogTf = EventListenerTouchOneByOne::create();
	catalogTf->onTouchBegan = handler;
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(catalogTf,catalogTTF);

	auto fileTf = EventListenerTouchOneByOne::create();
	fileTf->onTouchBegan = handler;
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(fileTf, fileTTF);
}