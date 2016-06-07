# 文件管理
项目目的
+ 熟悉文件存储空间的管理
+ 熟悉文件的物理结构、目录结构和文件操作
+ 熟悉文件系统管理实现
+ 加深对文件系统内部功能和实现过程的理解

## 项目要求
+ 在内存中开辟一个空间作为文件存储器，在其上实现一个简单的文件系统。退出这个文件系统时，需要该文件系统的内容保存到磁盘上，以便下次可以将其恢复到内存中来。
+ 文件系统提供的操作：
	+ 格式化
	+ 创建子目录
	+ 删除子目录
	+ 显示目录
	+ 更改当前目录
	+ 创建文件
	+ 打开文件
	+ 关闭文件
	+ 写文件
	+ 读文件
	+ 删除文件
	
## 项目实现
### 开发环境
**windows** + **VS2015** + **Cocos3.11**
### 算法分析
#### 设计理念
  本项目当中使用<font color = red>**沙盒化**</font>的概念，启动程序后会在c盘下建立workRoom文件夹作为程序的工作文件夹。程序实际上模拟了操作系统当中对文件管理的各项操作。程序关闭时考虑到对用户使用安全的考虑，并没有对文件夹进行情况操作，所以**最好每次启动之前删除本地已有的c:\workRoom文件夹**。
#### 文件目录结构
  本项目中仅支持文件夹以及txt文件的建立，所以文件之间维护了文件夹与文件夹，文件夹与文件之间的结构。这里利用了<font color = red>**多叉树的数据结构**</font>，文件夹节点会储存该文件夹下的所有文件以及文件夹。因为是使用多叉树的结构，所以不支持多个文件夹共享一个文件夹或文件，并且在删除一个文件夹的时候，会删除掉这个节点以及它的所有叶子节点，即删除这个文件夹下的所有内容。
  
  在实现过程当中，我用**head数组**和**fileVec数组**来模拟链表完成多叉树的增加和删除操作。
#### 文件索引
  文件的内容索引利用了显示链接FTA技术，将指向所有地址的指针保存在**FTA数组**当中，可以方便的配合文件目录结构对文件进行访问、删除、新建操作。
#### 内存管理
  本项目中的内存分配使用了**最先适配算法**:
  
+ **算法思想：**按分区先后次序从头查找，找到符合要求的第一个分区。
+ **算法实质：**尽可能利用存储区低地址空闲区，尽量在高地址部分保存较大空闲区，以便一旦有分配大空闲区要求时，容易得到满足
+ **算法优点：**分配简单，合并相邻空闲区也比较容易
+ **算法缺点：**查找总是从表首开始，前面空闲区往往被分割的很小，满足分配要求的可能性较小，查找次数较多。

实现的过程中，我设置了：

+ **freeMemoryArray数组 :** 储存空内存块
+ **fileToNum数组 :** 该映射表用来储存这个文件在freeMemoryArray中的位置
+ **增加文件时 :** 扫描freeMemoryArray数组，找到第一个能够存放该任务的空内存块。然后将其放入该内存块当中，freeMemoryArray数组的这个位置分解为两部分内存块，一部分为该任务所占据的内存块，一部分为剩下的空内存块。然后在视图区添加一个有色方块，并利用操作后的freeMemoryArray数组更新列表区。
+ **删除文件时 :** <font color = red>在freeMemoryArray数组中从任务所在位置往前扫描找到第一个类型不为2的方块，如果这个类型不为2的方块的类型为0，这两个方块合并。再从任务所在位置往后扫描找到第一个类型不为2的方块，如果这个类型不为2的方块的类型为0，这两个方块合并。</font>

#### 对本地的操作
利用c++的system函数调用DOS命令对本地文件进行操作:

+ **cd :** 打开文件(夹)
+ **del :** 删除文件
+ **rd :** 删除文件夹

#### 具体实现

```C++

class ViewLayer:
	public Layer
{
private:
	//剩余内存大小
	int memoryLarge;
public:
	//添加文件
	bool addFile(CCString name);
	//添加文件夹
	bool addCatalog(CCString name);
	//检查名字是否合法
	bool checkName(CCString name);
	//删除文件夹
	void deleteCatalog(int num);
	//删除文件
	void deleteFile(int num);
	//更新文件夹结构
	void addList(int num);
	//分配内存
	int findAdress(int size);
public:
	//更新视图
	void updataView();
};


//文件(夹)类
class File:
	public Sprite
{
/*
	type = 0为目录 type = 1为文件
	目录没有大小 
	文件有大小
*/
private:
	//名字
	CCString name;
	int type;
	//内存中的起始地址
	int adress;
	//内存中所占的大小
	int memoryLong;
	//是否被删除了
	bool isLive;
	//是第几个文件(夹)
	int num;
	//文件(夹)路径
	string path;
	//是否是根文件夹
	bool isRoot;
public:
	File(CCString name,int type, int adress, int memoryLong);
	File();
	~File();
public:
	void setName(CCString name);
	CCString getName();
	void setType(int type);
	int getType();
	void setAdress(int adress);
	int getAdress();
	void setMemoryLong(int memoryLong);
	int getMemoryLong();
	void setIsLive(bool isLive);
	bool getIsLive();
	CCString getFile();
	void setNum(int num);
	int getNum();
	void setPath(string fathrePath);
	string getPath();
	void setIsRoot(bool isRoot);
	bool getIsRoot();
};

//删除文件
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

//新建文件
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

```

### 界面展示
+ **文件夹页面介绍**<p>![pic0](http://o8efk558i.bkt.clouddn.com/main.png)
+ **文件页面介绍**<p>![pic01](http://o8efk558i.bkt.clouddn.com/main2.png)
+ **进入程序，程序会在c盘下建立workRoom文件夹**<p>![pic1](http://o8efk558i.bkt.clouddn.com/pic1.png)
+ **新建一个名为a的文件（可以看到剩余空间变小）**</p>![pic2](http://o8efk558i.bkt.clouddn.com/pic2.png)
+ **打开这个文件，可以看见文本内容，在内存中的地址，所占空间**![pic3](http://o8efk558i.bkt.clouddn.com/pic3.png)
+ **修改这个文件的文本内容，并点击保存**![pic4](http://o8efk558i.bkt.clouddn.com/pic4.png)
+ **新建一个名为bb的文件夹**</p>![pic5](http://o8efk558i.bkt.clouddn.com/pic5.png)
+ **进入bb文件夹（可以看到路径会随之变化）**![pic6](http://o8efk558i.bkt.clouddn.com/pic6.png)
+ **可以看到本地 c:\workRoom 文件夹当中有我们新建的文件**![pic7](http://o8efk558i.bkt.clouddn.com/pic7.png)
+ **在该路径下新建名为lalalalalala的文件**![pic8](http://o8efk558i.bkt.clouddn.com/pic8.png)
+ **打开这个文件，可以看见文本内容，在内存中的地址，所占空间**![pic9](http://o8efk558i.bkt.clouddn.com/pic9.png)
+ **退回到文件夹中，按删除按钮删除该文件**![pic10](http://o8efk558i.bkt.clouddn.com/pic10.png)
+ **点击退回按钮，退回到 c:\workRoom 文件夹下**![pic11](http://o8efk558i.bkt.clouddn.com/pic11.png)
+ **输入文件夹名后点击文件夹删除按钮删除bb文件夹**![pic12](http://o8efk558i.bkt.clouddn.com/pic12.png)
+ **输入文件夹名后点击文件夹建立按钮建立haha文件夹**![pic13](http://o8efk558i.bkt.clouddn.com/pic13.png)
+ **进入haha文件夹下建立lalalalalala文件**![pic14](http://o8efk558i.bkt.clouddn.com/pic14.png)
+ **点击格式化按钮，格式化 c:\workRoom 文件夹，并退回到 c:\workRoom 文件夹下**![pic15](http://o8efk558i.bkt.clouddn.com/pic15.png)
+ **新建lalalala文件和hahaha文件夹**![pic16](http://o8efk558i.bkt.clouddn.com/pic16.png)
+ **点开本地 c:\workRoom 文件夹，可以看到现在的所有文件**![pic17](http://o8efk558i.bkt.clouddn.com/pic17.png)
