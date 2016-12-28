#include "Folder.h"

Folder::Folder()
{
	this->isLive = true;
}

Folder::Folder(System* system, int headIndex, CCString name, string path, bool isRoot)
{
	this->system = system;
	this->headIndex = headIndex;
	this->name = name;
	this->isLive = true;
	this->isRoot = isRoot;
	this->fileVecIndex = fileVecIndex;
	this->setPath(path);
}

Folder::~Folder()
{
}

void Folder::setIsRoot(bool isRoot)
{
	this->isRoot = isRoot;
}

bool Folder::getIsRoot()
{
	return isRoot;
}

void Folder::addList(int num)
{
	// ��ȡϵͳ��Ϣ
	int* head = this->system->getHead();
	linkItem* link = this->system->getFileArr();
	Vector<SystemFile*> fileVec = this->system->getFileVec();
	int fileArrNum = this->system->getFileArrNum();

	// ��ӵ㵽������
	int nowNum = this->headIndex;
	fileArrNum++;
	link[fileArrNum].num = num;
	link[fileArrNum].ne = head[nowNum];
	head[nowNum] = fileArrNum;
}

void Folder::deleteSelf()
{
	// ��ȡϵͳ��Ϣ
	int* head = this->system->getHead();
	linkItem* link = this->system->getFileArr();
	Vector<SystemFile*> fileVec = this->system->getFileVec();

	// ɾ������
	int p = head[this->headIndex];
	while (p != 0)
	{
		fileVec.at(link[p].num)->deleteSelf();
		p = link[p].ne;
	}

	// ɾ���Լ�����ڵ�
	this->isLive = false;

	// �ڵ�����ʽĿ¼��ɾ������ļ���
	string command = "rd /s /q " + this->path;
	std::system(command.c_str());
}

bool Folder::createFolder(Folder* father, CCString name)
{
	// ��ȡϵͳ��Ϣ
	System* thisSystem = father->system;
	int* head = thisSystem->getHead();
	linkItem* link = thisSystem->getFileArr();
	Vector<SystemFile*> fileVec = thisSystem->getFileVec();
	int fileArrNum = thisSystem->getFileArrNum();

	
	if (father->checkName(name))
	{
		Folder * doc = new Folder(thisSystem, thisSystem->getFileVec.size(), name, father->path, true);
		thisSystem->getFileVec.pushBack(doc);
		father->addList(doc->getFileVecIndex());

		//�ڵ�����ʵĿ¼���½�����ļ���
		string command = "md " + doc->getPath();
		std::system(command.c_str());
		return true;
	}
	else 
		return false;
}
