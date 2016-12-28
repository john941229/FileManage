# 设计模式
## 重构思路
+ 我们的重构目标是**使得代码层类高内聚、低耦合，层级关系明确，层级的负责关系明确。关键类的代码量进行分离，最终使的代码易读，易维护，易拓展。**

## 重构过程
### 寻找发现项目问题
+ 我们重读了项目以后发现该项目中，类抽象粒度太低，很多本来应该在类中完成的方法被放在了类外去声明实现。导致项目的耦合度非常的高，一些关键的类中的代码量非常的大。并且项目中的分层非常不明确，导致数据流和界面放在了一起去写，关键类中的思路非常的混乱。所以我们之后准备对代码进行更细粒度的类的抽象和分层，先形成一个良好的代码结构。
+ 重构前的ViewLayer类
	+ ![p1](../resource/p1.png)
+ 重构前的ViewLayer类的代码量
	+ ![p2](../resource/p2.png)
+ 重构前的类图
	+ ![p3](../resource/p3.png) 
	
### 细粒度的类抽象和分层
+ 经过仔细思考以后，为了达到低耦合、高内聚、方便维护等的高质量代码。我们首先将数据流和界面拆分开，我们通过分析项目发现数据流主要是对一系列文件相关的类进行操作，并且有很多系统的数据结构一旦被创建需要在全局当中引用。所以我们主要将代码拆分为全局引用的**Static层**，由一些组件聚集的**View层**和控制数据流和模型的**File层**。
+ 之后再对File层中，通过对父级的**SystemFile类**的继承，抽象出更具体的**Folder类**和**Document类**。对**View层**中的Button组件进行重新的封装，因为项目当中不同功能的Button组件较多，所以对重新封装的**MyButton类**的继承，抽象出更具体的8种Button类。对Static层因为功能的不同，抽象出主要装载系统数据流的**System类**和主要装载系统View参数的**ViewSystem类**。

### 添加设计模式
+ 在通过上一步的抽象分层后，代码形成了明确的层级关系，基本实现了层间低耦合，层内高内聚的特征。但是我们还发现有些部分的代码重用性很高，需要重新进行封装。类之间通过继承的关系来扩展类的功能很不灵活等原因。我们将引入一些设计模式来对代码进行二次的重构。
+ 设计模式的使用思路将在第三大点当中具体提到。
+ 重构后的ViewLayer类
	+ ![p4](../resource/p4.png)
+ 重构后的ViewLayer类的代码量
	+ ![p5](../resource/p5.png) 
+ 重构后的类图
	+ ![p6](../resource/p6.png)
+ 重构后的结构图
	+ ![p9](../resource/p9.png)  

## 设计模式
+ 工厂模式
	+ 我们通过分析发现，File层的继承关系和View层的Button的继承关系，我们可以利用起来构造工厂。这样做的好处有两点：
		+ **第一点** 是需要修改初始化代码的时候，我们只需要去修改具体的类的构造函数，不需要去多处实例化的代码中去修改，比较好维护。
		+ **第二点** 是如果再添加继承父类的子类的时候，只需要添加一个类，然后去工厂里面添加一个生产过程就行，易于扩展。
	+ File工厂类图
		+ ![p7](../resource/p7.png)
	+ Button工厂类图
		+ ![p8](../resource/p8.png) 
+ 单例模式
	+ 因为我们是使用的cocos2dx引擎，所以需要遵守它内部的一些机制，比如说一个Director不能被二次实例化等。CCDirector单例，它负责管理初始化OpenGL渲染窗口以及游戏场景的流程控制，它是cocos2dx游戏开发中必不可少的类之一。为什么要把此类设计成单例对象呢？因为，一个游戏只需要有一个游戏窗口就够了，所以，只需要初始化一次OpenGL渲染窗口。而且场景的流程控制功能，也只需要存在一个这样的场景控制对象即可。为了保证CCDirector类只存在一个实例对象，就必须使用单例模式。所以我们马上联想到了单例模式能够帮助我们方便的完成这些特性，所以我们选用了单例模式来实现一些继承Director类的子类的构造函数。 
+ 装饰器模式
	+ 当我们发现一些关键类的功能越来越复杂，代码量越来越大的时候。我们想了一下可不可以不通过继承关系来对类进行拓展，然后我们就想到了装饰器模式。我们把类中的get、set以及重写父类的方法保留在类本身当中。将其他的拓展方法转移到类的装饰器中的方法来对类进行横向拓展。简化了一些关键类中的核心代码，更易于维护。

## 重构后的代码
### 全局System类
```C++
class System
{
private:
	// 系统容积
	static int memoryLarge;
	// FTA
	static int FTA[1000];
	// 文件数组
	static Vector<SystemFile*> fileVec;
	// 空内容块数组
	static Vector<freeMemory*> freeMemoryArr;
	// 第几块内存的起始
	static std::map<int, int> fileToVec;
	// 数组模拟链表
	static FileTree* fileTree;
public:
	System();
	~System();
public:
	int getMemoryLarge();
	void setFileVec(Vector<SystemFile*> fileVec);
	Vector<SystemFile*> getFileVec();
	void setFreeMemoryArr(Vector<freeMemory*> freeMemoryArr);
	Vector<freeMemory*> getFreeMemoryArr();
	void setFileToVec(std::map<int, int> fileToVec);
	std::map<int, int> getFileToVec();
	FileTree* getFileTree();
public:
	static void createMySelf();
	bool reduceMemoryLarge(int size);
	void addMemoryLarge(int size);
};


System::System()
{
}

System::~System()
{
}

void System::createMySelf()
{
	system("cd c:\\");

	// 初始化变量
	memoryLarge = 1048576;
	freeMemory *freememory = new freeMemory(0, memoryLarge, 0);
	freeMemoryArr.pushBack(freememory);

	// 新建根目录
	Folder * folder = new Folder(0, (CCString*) "workRoom", "c:", true);
	fileVec.pushBack(folder);
	string command = "md " + folder->getPath();
	system(command.c_str());
}

bool System::reduceMemoryLarge(int size)
{
	if (this->memoryLarge >= size) 
	{
		this->memoryLarge -= size;
		return true;
	}
	else 
	{
		return false;
	}
}

void System::addMemoryLarge(int size)
{
	this->memoryLarge += size;
}

```

### CreateFolderButton类
```C++
class CreateFolderButton :
	public MyButton
{
private:
	ViewLayer* viewLayer;
public:
	CreateFolderButton(ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY);
	~CreateFolderButton();
public:
	void event(cocos2d::Ref* pSender);
	void createMySelf(Menu* menuButton, int positionX, int positionY);
};


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

```

### SystemFile类
```C++
class SystemFile:
	public Sprite
{
protected:
	// 在system中的index
	int headIndex;
	// 文件名
	CCString* name;
	// 是否有效
	bool isLive;
	// 真实文件路径
	string path;
	// 是否是系统的根节点
	bool isRoot;
	// 文件类型
	int type;
public:
	SystemFile();
	~SystemFile();
public:
	void setType(int type);
	int getType();
	void setName(CCString* name);
	CCString* getName();
	void setIsLive(bool isLive);
	bool getIsLive();
	void setPath(string fathrePath);
	string getPath();
	void setHeadIndex(int headIndex);
	int getHeadIndex();
	void setIsRoot(bool isRoot);
	bool getIsRoot();
public:
	// 删除自己
	virtual void deleteSelf();
};


SystemFile::SystemFile()
{
}

SystemFile::~SystemFile()
{
}

void SystemFile::setType(int type)
{
	this->type = type;
}

int SystemFile::getType()
{
	return this->type;
}

void SystemFile::setName(CCString* name)
{
	this->name = name;
}

CCString* SystemFile::getName()
{
	return this->name;
}

void SystemFile::setIsLive(bool isLive)
{
	this->isLive = isLive;
}

bool SystemFile::getIsLive()
{
	return isLive;
}

void SystemFile::setPath(string fathrePath)
{
	fathrePath = fathrePath + "\\";
	path = fathrePath + name->getCString();
}

string SystemFile::getPath()
{
	return this->path;
}

void SystemFile::setHeadIndex(int headIndex)
{
	this->headIndex = headIndex;
}

int SystemFile::getHeadIndex()
{
	return this->headIndex;
}

void SystemFile::deleteSelf()
{

}

void SystemFile::setIsRoot(bool isRoot)
{
	this->isRoot = isRoot;
}

bool SystemFile::getIsRoot()
{
	return isRoot;
}

```

### SystemFileDector类
```C++
class SystemFileDecorator
{
private:
	SystemFile* systemFile;
public:
	SystemFileDecorator(SystemFile* systemFile);
	~SystemFileDecorator();
	// 检查name是否是儿子节点的名字(不允许一个儿子节点下同名)
	bool checkName(CCString* name);
	// 寻找系统中的内存最适空闲位置
	int findAdress(int size);
};

SystemFileDecorator::SystemFileDecorator(SystemFile* systemFile)
{
	this->systemFile = systemFile;
}

SystemFileDecorator::~SystemFileDecorator()
{

}

bool SystemFileDecorator::checkName(CCString* name)
{
	// 获取系统信息
	System* system = new System();
	FileTree* fileTree = system->getFileTree();
	int* head = fileTree->head;
	linkItem* link = fileTree->fileArr;
	Vector<SystemFile*> fileVec = system->getFileVec();

	// 查看是否重名
	int p = head[this->systemFile->getHeadIndex()];
	while (p != 0)
	{
		string nameStr = name->getCString();
		string getnameStr = system->getFileVec.at(link[p].num)->getName().getCString();
		if (nameStr == getnameStr && system->getFileVec.at(link[p].num)->getIsLive())
		{
			return false;
		}
		p = link[p].ne;
	}
	return true;
}

int SystemFileDecorator::findAdress(int size)
{
	System* system = new System();
	Vector<freeMemory*> freeMemoryArr = system->getFreeMemoryArr();
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
```

### ButtonFactory 类
```C++
class  ButtonFactory
{
public:
	ButtonFactory();
	~ButtonFactory();
	MyButton* createButton(int type, ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY);
};

ButtonFactory::ButtonFactory()
{
}

ButtonFactory::~ButtonFactory()
{
}

MyButton* ButtonFactory::createButton(int type, ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY)
{
	MyButton* button = NULL;
	switch (type)
	{
		case 0:
		{
			button = new BackOffButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 1:
		{
			button = new ClearButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 2:
		{
			button = new CreateDocumentButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 3:
		{
			button = new CreateFolderButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 4:
		{
			button = new DeleteFolderButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 5:
		{
			button = new DeleteDocumentButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 6:
		{
			button = new EnterFolderButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 7:
		{
			button = new EnterDocumentButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		default:
			break;
	}
	return button;
}
```

## Director单例方法

```C++
Director* Director::getInstance()
{
    if (!s_SharedDirector)
    {
        s_SharedDirector = new (std::nothrow) DisplayLinkDirector();
        CCASSERT(s_SharedDirector, "FATAL: Not enough memory");
        s_SharedDirector->init();
    }

    return s_SharedDirector;
}
```
