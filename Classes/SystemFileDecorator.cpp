#include "SystemFileDecorator.h"

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