#include "FileTree.h"

FileTree::FileTree()
{
	fileArrNum = 0;
	memset(head, 0, sizeof(head));
}

FileTree::~FileTree()
{
}

int FileTree::addList(int fatherIndex, int headIndex)
{
	linkItem* item = new linkItem();
	fileArrNum++;
	fileArr[fileArrNum].ne = head[headIndex];
	fileArr[fileArrNum].num = headIndex;
	head[headIndex] = fileArrNum;
}

void FileTree::deleteSonTree(int headIndex)
{
	System* system = new System();
	auto fileVec = system->getFileVec();

	// É¾µô×ÓÊ÷
	int p = head[headIndex];
	while (p != 0)
	{
		fileVec.at(fileArr[p].num)->deleteSelf();
		p = fileArr[p].ne;
	}
}