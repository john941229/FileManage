#include "FileShow.h"

FileShow::FileShow()
{
}

FileShow::FileShow(CCString filePath, int adress, int memoryLong)
{
	this->filePath = filePath;
	this->adress = adress;
	this->memoryLong = memoryLong;
	init();
}

FileShow::~FileShow()
{
}

bool FileShow::init()
{
	char essay[10000],readStr[1000];
	memset(essay, '\0', sizeof(essay));

	//添加背景图
	Sprite * backGround = Sprite::create("backGroundM.png");
	Size size = Director::getInstance()->getWinSize();
	visiblesize = Director::getInstance()->getVisibleSize();
	backGround->setPosition(size.width / 2, size.height / 2);
	float spx = backGround->getTextureRect().getMaxX();
	float spy = backGround->getTextureRect().getMaxY();
	backGround->setScaleX(size.width / spx);
	backGround->setScaleY(size.height / spy);
	addChild(backGround);

	//添加输入框
	ttf = new TextFieldTTF();
	ttf->setPosition(60, visiblesize.height - 110);
	ttf->setAnchorPoint(Vec2::ZERO);
	ttf->setSystemFontSize(20);
	string file = this->filePath.getCString();
	file = file + ".txt";
	freopen(file.c_str(), "r", stdin);
	while (gets_s(readStr))
	{
		strcat(essay, readStr);
	}
	fclose(stdin);
	ttf->setString(essay);
	addChild(ttf);

	//添加内存信息显示
	information = new TextFieldTTF();
	char info[200];
	memset(info, '\0', sizeof(info));
	sprintf(info, "adress : %d  volume: %d", adress, memoryLong);
	information->setString(info);
	information->setSystemFontSize(30);
	information->setTextColor(Color4B::BLACK);
	information->setPosition(visiblesize.width / 2, visiblesize.height - 30);
	addChild(information);

	//添加保存和返回button
	auto loadButton = MenuItemImage::create("addButton.png", "addButton.png",
											CC_CALLBACK_1(FileShow::loadFileButton, this));
	loadButton->setPosition(visiblesize.width / 2, 70);
	loadButton->setScale(2);
	auto backButton = MenuItemImage::create("delete.png", "delete.png",
											CC_CALLBACK_1(FileShow::backOffButton, this));
	backButton->setPosition(visiblesize.width - 36, visiblesize.height - 30);
	backButton->setScale(2);

	menu = Menu::create(loadButton, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
	menu->addChild(backButton);

	addListener();
	return true;
}

void FileShow::loadFileButton(Ref* Spender)
{
	string file = this->filePath.getCString();
	file = file + ".txt";
	freopen(file.c_str(), "w", stdout);
	cout << ttf->getString() << endl;
	fclose(stdout);
}

void FileShow::backOffButton(Ref* Spender)
{
	Director::getInstance()->getRunningScene()->removeChild(this);
}

void FileShow::addListener()
{
	auto director = Director::getInstance();
	auto handler = [=](Touch* t, Event* e)
	{
		auto target = e->getCurrentTarget();
		if (target->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (ttf == target)
			{
				ttf->attachWithIME();
			}
		}
		return false;
	};

	auto tf = EventListenerTouchOneByOne::create();
	tf->onTouchBegan = handler;
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tf,ttf);
}

void FileShow::setFromNum(int num)
{
	this->fromNum = num;
}
