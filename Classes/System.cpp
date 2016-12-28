#include "System.h"

System::System()
{
	system("cd c:\\");

	// 初始化变量
	memoryLarge = 1048576;
	memset(head, 0, sizeof(head));
	fileArrNum = 0;
	freeMemory *freememory = new freeMemory(0, memoryLarge, 0);
	freeMemoryArr.pushBack(freememory);

	// 新建根目录
	Folder * folder = new Folder(this, fileVec.size(), "workRoom", "c:", true);
	fileVec.pushBack(folder);
	string command = "md " + folder->getPath();
	system(command.c_str());
}

System::~System()
{
}

int* System::getHead()
{
	return this->head;
}

Vector<SystemFile*> System::getFileVec()
{
	return this->fileVec;
}

linkItem* System::getFileArr()
{
	return this->fileArr;
}

int System::getFileArrNum()
{
	return this->fileArrNum;
}

Vector<freeMemory*> System::getFreeMemoryArr() 
{
	return this->freeMemoryArr;
}

std::map<int, int> System::getFileToVec()
{
	return this->fileToVec;
}

bool System::reduceMemoryLarge(int size)
{
	if (this->memoryLarge >= size) 
	{
		this->memoryLarge -= size;
		return true;
	}
	else 
	{
		return false;
	}
}
