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
	// 获取系统信息
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	FileTree* fileTree = system->getFileTree();
	// 删掉子树
	fileTree->deleteSonTree(this->headIndex);
	// 删掉自己这个节点
	this->isLive = false;

	// 在电脑正式目录下删除这个文件夹
	string command = "rd /s /q " + this->path;
	std::system(command.c_str());
}

bool Folder::createFolder(Folder* father, CCString* name)
{
	// 获取系统信息
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	SystemFileDecorator* fatherDecorator = new SystemFileDecorator(father);

	if (fatherDecorator->checkName(name))
	{
		Folder * doc = new Folder(system->getFileVec.size(), name, father->path, true);
		system->getFileVec.pushBack(doc);
		FolderDecorator* fatherFolderDecorator = new FolderDecorator(father);
		fatherFolderDecorator->addList(doc->getHeadIndex());

		//在电脑真实目录下新建这个文件夹
		string command = "md " + doc->getPath();
		std::system(command.c_str());
		return true;
	}
	else 
		return false;
}
