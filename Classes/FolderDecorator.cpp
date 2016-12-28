#include "FolderDecorator.h"

FolderDecorator::FolderDecorator(Folder* folder)
{
	this->folder = folder;
}

FolderDecorator::~FolderDecorator()
{

}

// 添加节点到链表中
void FolderDecorator::addList(int num)
{
	// 获取系统信息
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	FileTree* fileTree = system->getFileTree();

	// 添加点到链表中
	fileTree->addList(num, this->folder->getHeadIndex());
}