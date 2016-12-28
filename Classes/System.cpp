#include "System.h"

System::System()
{
}

System::~System()
{
}

void System::createMySelf()
{
	system("cd c:\\");

	// 初始化变量
	memoryLarge = 1048576;
	freeMemory *freememory = new freeMemory(0, memoryLarge, 0);
	freeMemoryArr.pushBack(freememory);

	// 新建根目录
	Folder * folder = new Folder(0, (CCString*) "workRoom", "c:", true);
	fileVec.pushBack(folder);
	string command = "md " + folder->getPath();
	system(command.c_str());
}

void System::setFreeMemoryArr(Vector<freeMemory*> freeMemoryArr)
{
	this->freeMemoryArr = freeMemoryArr;
}

void System::setFileToVec(std::map<int, int> fileToVec)
{
	this->fileToVec = fileToVec;
}

void System::setFileVec(Vector<SystemFile*> fileVec)
{
	this->fileVec = fileVec;
}

Vector<SystemFile*> System::getFileVec()
{
	return this->fileVec;
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

void System::addMemoryLarge(int size)
{
	this->memoryLarge += size;
}

FileTree* System::getFileTree()
{
	return this->fileTree;
}

int System::getMemoryLarge()
{
	return this->memoryLarge;
}