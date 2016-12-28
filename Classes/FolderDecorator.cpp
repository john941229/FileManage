#include "FolderDecorator.h"

FolderDecorator::FolderDecorator(Folder* folder)
{
	this->folder = folder;
}

FolderDecorator::~FolderDecorator()
{

}

// ��ӽڵ㵽������
void FolderDecorator::addList(int num)
{
	// ��ȡϵͳ��Ϣ
	System* system = new System();
	Vector<SystemFile*> fileVec = system->getFileVec();
	FileTree* fileTree = system->getFileTree();

	// ��ӵ㵽������
	fileTree->addList(num, this->folder->getHeadIndex());
}