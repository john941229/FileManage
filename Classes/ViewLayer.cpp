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
	catalogTTF = new TextFieldTTF();
	fileTTF = new TextFieldTTF();
	catalogTTF->setString("Entry the name of catalog!");
	catalogTTF->setSystemFontSize(20);
	catalogTTF->setPosition(visibleSize.width / 2 - 60, 50);
	addChild(catalogTTF);
	fileTTF->setString("Entry the name of file!");
	fileTTF->setSystemFontSize(20);
	fileTTF->setPosition(visibleSize.width / 2 - 60, 100);
	addChild(fileTTF);
	addListener();

	auto addCatalogButton = MenuItemImage::create("addButton.png", "addButton.png",
		CC_CALLBACK_1(ViewLayer::addCatalogButton, this));
	addCatalogButton->setPosition(visibleSize.width/ 2 + 75 , 50);
	menuButton->addChild(addCatalogButton);
	addCatalogButton->setScale(1.6);

	auto addFileButton = MenuItemImage::create("addButton.png", "addButton.png",
		CC_CALLBACK_1(ViewLayer::addFileButton, this));
	addFileButton->setPosition(visibleSize.width / 2 + 75, 100);
	addFileButton->setScale(1.6);
	menuButton->addChild(addFileButton);

	auto clickCatalogButton = MenuItemImage::create("clickTo.png", "clickTo.png",
		CC_CALLBACK_1(ViewLayer::clickCatalog, this));
	clickCatalogButton->setPosition(visibleSize.width / 2 + 115, 50);
	clickCatalogButton->setScale(1.6);
	menuButton->addChild(clickCatalogButton);

	auto clickFileButton = MenuItemImage::create("clickTo.png", "clickTo.png",
		CC_CALLBACK_1(ViewLayer::clickFile, this));
	clickFileButton->setPosition(visibleSize.width / 2 + 115, 100);
	clickFileButton->setScale(1.6);
	menuButton->addChild(clickFileButton);

	auto deleteCatalogButton = MenuItemImage::create("delete.png", "delete.png",
		CC_CALLBACK_1(ViewLayer::deleteCatalogButton, this));
	deleteCatalogButton->setPosition(visibleSize.width / 2 + 155, 50);
	deleteCatalogButton->setScale(1.6);
	menuButton->addChild(deleteCatalogButton);

	auto deleteFileButton = MenuItemImage::create("delete.png", "delete.png",
		CC_CALLBACK_1(ViewLayer::deleteFileButton, this));
	deleteFileButton->setPosition(visibleSize.width / 2 + 155, 100);
	deleteFileButton->setScale(1.6);
	menuButton->addChild(deleteFileButton);

	auto backOffButton = MenuItemImage::create("backOff.png", "backOff.png",
		CC_CALLBACK_1(ViewLayer::backOffButton, this));
	backOffButton->setPosition(42, visibleSize.height - 120);
	backOffButton->setScale(2);
	menuButton->addChild(backOffButton);

	auto clearButton = MenuItemImage::create("clear.png", "clear.png",
		CC_CALLBACK_1(ViewLayer::clearBtton, this));
	clearButton->setPosition(visibleSize.width / 2 + 215, 100);
	clearButton->setScale(2);
	menuButton->addChild(clearButton);
}

void ViewLayer::initUI()
{
	//添加背景
	Sprite * backGround = Sprite::create("backGroundN.png");
	Size size = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();
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
	showPath->setPosition(240, visibleSize.height - 130);
	addChild(showPath);

	showMemory = new TextFieldTTF();
	char info[100];
	sprintf(info, "Additional Memory: %d KB", memoryLarge);
	showMemory->setString(info);
	showMemory->setSystemFontSize(30);
	showMemory->setTextColor(Color4B::BLACK);
	showMemory->setPosition(visibleSize.width / 2, visibleSize.height - 30);
	addChild(showMemory);

	menuButton = Menu::create(NULL);
	menuButton->setPosition(Vec2::ZERO);
	addChild(menuButton);
	addFunctionButton();
}

// 已改写
bool ViewLayer::init()
{
	system("cd c:\\");
	memoryLarge = 1048576;
	initUI();
	
	//初始化变量
	memset(head, 0, sizeof(head));
	fileArrNum = 0;
	freeMemory *freememory = new freeMemory(0, memoryLarge, 0);
	freeMemoryArr.pushBack(freememory);

	//新建根目录
	File * file = new File("workRoom", 0, 0, 0);
	file->setPath("c:");
	file->setNum(0);
	file->setIsRoot(true);
	fileVec.pushBack(file);
	string command = "md " + file->getPath();
	system(command.c_str());
	newfile = file;

	return true;
}

// 已改写
void ViewLayer::addList(int num)
{
	int nowNum = newfile->getNum();
	fileArrNum++;
	fileArr[fileArrNum].num = num;
	fileArr[fileArrNum].ne = head[nowNum];
	head[nowNum] = fileArrNum;
}


// 已改写
bool ViewLayer::checkName(CCString name)
{
	int nowNum = newfile->getNum();
	int p = head[nowNum];
	while (p != 0)
	{
		string nameStr = name.getCString();
		string getnameStr = fileVec.at(fileArr[p].num)->getName().getCString();
		if (nameStr == getnameStr && fileVec.at(fileArr[p].num)->getIsLive())
		{
			return false;
		}
		p = fileArr[p].ne;
	}
	return true;
}

// 已改写
int ViewLayer::findAdress(int size)
{
	int p = 0, q = -1;
	int min = 10000000;
	for (auto &e : freeMemoryArr)
	{
		if (e->getLong() >= size && e->getLong() <= min && e->getType() == 0)
		{
			min = e->getLong();
			q = p;
		}
		p++;
	}

	return q;
}

// 已改写
bool ViewLayer::addFile(CCString name)
{
	//在硬盘上创建该文件
	File * file = new File(name,1, 0, 0);
	file->setPath(newfile->getPath());
	string nameStr = file->getPath();
	string filename = nameStr + ".txt";

	//将内容写入该文件
	freopen(filename.c_str(), "w", stdout);
	cout << file->getName().getCString() << ".txt" << endl;
	fclose(stdout);

	//获取文件的大小
	const char *filepath = filename.c_str();
	struct _stat info;
	_stat(filepath, &info);
	int size = info.st_size;

	int adress = findAdress(size);
	//满足内存限制
	if (adress != -1)
	{
		//处理内存块
		int s = freeMemoryArr.at(adress)->getStart();
		int l = freeMemoryArr.at(adress)->getLong();
		freeMemoryArr.at(adress)->setLong(size);
		freeMemoryArr.at(adress)->setType(1);
		freeMemory *f = new freeMemory(s + size, l - size, 0);
		freeMemoryArr.insert(adress + 1, f);

		//处理file信息
		memoryLarge -= size;
		fileVec.pushBack(file);
		file->setNum(fileVec.size() - 1);
		addList(file->getNum());
		file->setMemoryLong(size);
		file->setAdress(freeMemoryArr.at(adress)->getStart());
		fileToVec[file->getNum()] = adress;
	}
	//不满足内存限制
	else
	{
		string command = "del " + filename;
		system(command.c_str());
		file->setIsLive(false);
		return false;
	}
	return true;
}

// 已改写
bool ViewLayer::addCatalog(CCString name)
{
	if (checkName(name))
	{
		File * file = new File(name,0, 0, 0);
		fileVec.pushBack(file);
		file->setNum(fileVec.size() - 1);
		addList(file->getNum());
		file->setPath(newfile->getPath());

		//在电脑真实目录下新建这个文件夹
		string command = "md " + file->getPath();
		system(command.c_str());
		return true;
	}
	else
		return false;
}

void ViewLayer::deleteFile(int num)
{
	//硬盘上删除该文件
	File* file = fileVec.at(num);
	file->setIsLive(false);
	string filename = file->getPath();
	filename = filename + ".txt";
	string command = "del " + filename;
	system(command.c_str());

	//维护内存块
	bool flag = true;
	int position = fileToVec[num];
	freeMemoryArr.at(position)->setType(0);

	int behind = position - 1;
	while (behind > 1 && freeMemoryArr.at(behind)->getType() == 2)
	{
		behind--;
	}
	int front = position + 1;
	while (front + 1 < freeMemoryArr.size() && freeMemoryArr.at(front)->getType() == 2)
	{
		front++;
	}

	if (behind >= 0 && freeMemoryArr.at(behind)->getType() == 0)
	{
		freeMemoryArr.at(behind)->setLong(freeMemoryArr.at(behind)->getLong() + fileVec.at(num)->getMemoryLong());
		freeMemoryArr.at(position)->setType(2);
		flag = false;
	}
	if (front < freeMemoryArr.size() && freeMemoryArr.at(front)->getType() == 0)
	{
		if (!flag)
		{
			freeMemoryArr.at(behind)->setLong(freeMemoryArr.at(behind)->getLong() + freeMemoryArr.at(front)->getLong());
			freeMemoryArr.at(position)->setType(2);
			freeMemoryArr.at(front)->setType(2);
		}
		else
		{
			freeMemoryArr.at(position)->setLong(freeMemoryArr.at(position)->getLong() + freeMemoryArr.at(front)->getLong());
			freeMemoryArr.at(front)->setType(2);
		}
	}
}

// 已改写
void ViewLayer::deleteCatalog(int num)
{
	File* file = fileVec.at(num);
	int p = head[num];
	while (p != 0)
	{
		if (fileVec.at(fileArr[p].num)->getType() == 0)
		{
			deleteCatalog(fileArr[p].num);
		}
		else
		{
			deleteFile(fileArr[p].num);
		}
		p = fileArr[p].ne;
	}
	file->setIsLive(false);
	string command = "rd /s /q " + file->getPath();
	system(command.c_str());
}

void ViewLayer::deleteFileButton(cocos2d::Ref* pSender)
{
	bool flag = false;
	const string fileName = fileTTF->getString();
	int num = 0;
	for (auto &e : fileVec)
	{
		if (e->getName().getCString() == fileName && e->getIsLive())
		{
			flag = true;
			break;
		}
		num++;
	}

	if (flag)
	{
		memoryLarge += fileVec.at(num)->getMemoryLong();
		deleteFile(num);
		updataView();
	}
}

void ViewLayer::deleteCatalogButton(cocos2d::Ref* pSender)
{
	const string catalogName = catalogTTF->getString();
	bool flag = false;
	int num = 0;
	for (auto &e : fileVec)
	{
		if (e->getName().getCString() == catalogName && e->getIsLive())
		{
			flag = true;
			break;
		}
		num++;
	}

	if (flag)
	{
		deleteCatalog(num);
		updataView();
	}
}

void ViewLayer::updataView()
{
	showPath->setString(newfile->getPath());
	char info[100];
	sprintf(info, "Additional Memory: %d KB", memoryLarge);
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
	posX = visibleSize.width / 2 - 190;
	posY = visibleSize.height / 2 + 185;

	//将所有要显示的文件、目录添加到vector中
	int num = newfile->getNum();
	int p = head[num];
	while (p != 0)
	{
		if (fileVec.at(fileArr[p].num)->getIsLive())
		{
			Sprite *sp;
			TextFieldTTF *spName = new TextFieldTTF();
			if (fileVec.at(fileArr[p].num)->getType() == 0)
			{
				sp = Sprite::create("catalog.png");
				spName->setString(fileVec.at(fileArr[p].num)->getName().getCString());
			}
			else
			{
				sp = Sprite::create("fileN.png");
				string filename = fileVec.at(fileArr[p].num)->getName().getCString();
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
				posX = visibleSize.width / 2 - 190;
				posY -= 75;
				count = count - 11;
			}
		}
		p = fileArr[p].ne;
	}
}

void ViewLayer::addFileButton(cocos2d::Ref* pSender)
{
	const string fileN = fileTTF->getString();
	CCString* fileName = CCString::create(fileN);
	if (addFile(*fileName))
	{
		//CCLOG("success");
		updataView();
	}
}

void ViewLayer::addCatalogButton(cocos2d::Ref* pSender)
{
	const string catalogN = catalogTTF->getString();
	CCString* catalogName = CCString::create(catalogN);
	if (addCatalog(*catalogName))
	{
		//CCLOG("success");
		updataView();
	}
}

void ViewLayer::clickFile(cocos2d::Ref* pSender)
{
	File * nowFile;
	bool flag = false;
	for (auto &e : fileVec)
	{
		if (e->getName().getCString() == fileTTF->getString())
		{
			nowFile = e;
			flag = true;
			break;
		}
	}

	if (flag)
	{
		FileShow * fileshow = new FileShow(nowFile->getPath(), nowFile->getAdress(), nowFile->getMemoryLong());
		fileshow->setFromNum(newfile->getNum());
		Director::getInstance()->getRunningScene()->addChild(fileshow);
	}
}

void ViewLayer::clickCatalog(cocos2d::Ref* pSender)
{
	bool flag = false;
	File* oldfile = fromfile;
	fromfile = newfile;
	for (auto &e : fileVec)
	{
		if (e->getName().getCString() == catalogTTF->getString())
		{
			newfile = e;
			flag = true;
			break;
		}
	}
	if (flag)
	{
		updataView();
	}
	else
	{
		fromfile = oldfile;
	}
}

void ViewLayer::backOffButton(cocos2d::Ref* pSender)
{
	if (!newfile->getIsRoot())
	{
		newfile = fromfile;
		updataView();
	}
	else
	{
		CCLOG("it is root,can't back off");
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

void ViewLayer::clearBtton(cocos2d::Ref* pSender)
{
	newfile = fileVec.at(0);
	for (auto &e : fileVec)
	{
		if (e->getIsLive() && e->getNum() != 0)
		{
			if (e->getType() == 0)
			{
				deleteCatalog(e->getNum());
			}
			else
			{
				deleteFile(e->getNum());
			}
		}
	}

	updataView();
}