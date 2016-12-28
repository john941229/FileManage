#include "SystemFile.h"

SystemFile::SystemFile()
{
}

SystemFile::~SystemFile()
{
}

void SystemFile::setName(CCString name)
{
	this->name = name;
}

CCString SystemFile::getName()
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
	path = fathrePath + name.getCString();
}

string SystemFile::getPath()
{
	return this->path;
}

void SystemFile::setSystem(System* system)
{
	this->system = system;
}

System* SystemFile::getSystem()
{
	return this->system;
}

void SystemFile::setHeadIndex(int headIndex)
{
	this->headIndex = headIndex;
}

int SystemFile::getHeadIndex()
{
	return this->headIndex;
}

bool SystemFile::checkName(CCString name)
{
	// 获取系统信息
	int* head = this->system->getHead();
	linkItem* link = this->system->getFileArr();
	Vector<SystemFile*> fileVec = this->system->getFileVec();

	// 查看是否重名
	int p = head[this->headIndex];
	while (p != 0)
	{
		string nameStr = name.getCString();
		string getnameStr = this->system->getFileVec.at(link[p].num)->getName().getCString();
		if (nameStr == getnameStr && this->system->getFileVec.at(link[p].num)->getIsLive())
		{
			return false;
		}
		p = link[p].ne;
	}
	return true;
}

int SystemFile::findAdress(int size)
{
	Vector<freeMemory*> freeMemoryArr = this->system->getFreeMemoryArr();
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

void SystemFile::deleteSelf()
{

}
