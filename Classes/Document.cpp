#include "Document.h"

Document::Document()
{
}

Document::Document(int headIndex, CCString* name, string path, int adress, int memoryLong)
{
	this->type = 1;
	this->headIndex = headIndex;
	this->name = name;
	this->adress = adress;
	this->memoryLong = memoryLong;
	this->isLive = true;
	this->setPath(path);
}

Document::~Document()
{
}

void Document::setAdress(int adress)
{
	this->adress = adress;
}

int Document::getAdress()
{
	return this->adress;
}

void Document::setMemoryLong(int memoryLong)
{
	this->memoryLong = memoryLong;
}

int Document::getMemoryLong()
{
	return this->memoryLong;
}

void Document::deleteSelf()
{
	System* system = new System();
	// 获取系统信息
	Vector<SystemFile*> fileVec = system->getFileVec();
	Vector<freeMemory*> freeMemoryArr = system->getFreeMemoryArr();
	std::map<int, int> fileToVec = system->getFileToVec();

	this->isLive = false;
	// 硬盘上删除该文件
	string filename = this->path;
	filename = filename + ".txt";
	string command = "del " + filename;
	std::system(command.c_str());

	// 维护内存块
	bool flag = true;
	int position = fileToVec[this->headIndex];
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
		freeMemoryArr.at(behind)->setLong(freeMemoryArr.at(behind)->getLong() + freeMemoryArr.at(position)->getLong());
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

bool Document::create(Folder* father, CCString* name)
{
	// 获取系统信息
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	Vector<freeMemory*> freeMemoryArr = system->getFreeMemoryArr();
	std::map<int, int> fileToVec = system->getFileToVec();
	FileTree* fileTree = system->getFileTree();
	SystemFileDecorator* fatherDecorator = new SystemFileDecorator(father);

	if (fatherDecorator->checkName(name))
	{
		Document * doc = new Document(system->getFileVec.size(), name, father->getPath(), -1, 0);
		SystemFileDecorator* docDecorator = new SystemFileDecorator(doc);
		// 在硬盘上创建该文件
		string nameStr = doc->getPath();
		string filename = nameStr + ".txt";

		// 将内容写入该文件
		freopen(filename.c_str(), "w", stdout);
		cout << doc->getName()->getCString() << ".txt" << endl;
		fclose(stdout);

		// 获取文件的大小
		const char *filepath = filename.c_str();
		struct _stat info;
		_stat(filepath, &info);
		int size = info.st_size;

		int adress = docDecorator->findAdress(size);
		// 满足内存限制
		if (adress != -1)
		{
			// 处理内存块
			int s = freeMemoryArr.at(adress)->getStart();
			int l = freeMemoryArr.at(adress)->getLong();
			freeMemoryArr.at(adress)->setLong(size);
			freeMemoryArr.at(adress)->setType(1);
			freeMemory *f = new freeMemory(s + size, l - size, 0);
			freeMemoryArr.insert(adress + 1, f);

			// 处理doc的其他属性
			system->reduceMemoryLarge(size);
			fileVec.pushBack(doc);
			father->addList(doc->getHeadIndex());
			doc->setMemoryLong(size);
			doc->setAdress(freeMemoryArr.at(adress)->getStart());
			fileToVec[doc->getHeadIndex()] = adress;
		}
		// 不满足内存限制
		else
		{
			string command = "del " + filename;
			std::system(command.c_str());
			doc->setIsLive(false);
			return false;
		}
		return true;
	}
}



