#include "Folder.h"

Folder::Folder()
{
	this->isLive = true;
}

Folder::Folder(int headIndex, CCString* name, string path, bool isRoot)
{
	this->type = 0;
	this->headIndex = headIndex;
	this->name = name;
	this->isLive = true;
	this->isRoot = isRoot;
	this->setPath(path);
}

Folder::~Folder()
{
}

void Folder::deleteSelf()
{
	// ��ȡϵͳ��Ϣ
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	FileTree* fileTree = system->getFileTree();
	// ɾ������
	fileTree->deleteSonTree(this->headIndex);
	// ɾ���Լ�����ڵ�
	this->isLive = false;

	// �ڵ�����ʽĿ¼��ɾ������ļ���
	string command = "rd /s /q " + this->path;
	std::system(command.c_str());
}

bool Folder::createFolder(Folder* father, CCString* name)
{
	// ��ȡϵͳ��Ϣ
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	SystemFileDecorator* fatherDecorator = new SystemFileDecorator(father);

	if (fatherDecorator->checkName(name))
	{
		Folder * doc = new Folder(system->getFileVec.size(), name, father->path, true);
		system->getFileVec.pushBack(doc);
		FolderDecorator* fatherFolderDecorator = new FolderDecorator(father);
		fatherFolderDecorator->addList(doc->getHeadIndex());

		//�ڵ�����ʵĿ¼���½�����ļ���
		string command = "md " + doc->getPath();
		std::system(command.c_str());
		return true;
	}
	else 
		return false;
}
