#include "File.h"

File::File()
{
}

File::~File()
{
}

File::File(CCString name, int type, int adress, int memoryLong)
{
	this->name = name;
	this->type = type;
	this->adress = adress;
	this->memoryLong = memoryLong;
	this->isLive = true;
	this->isRoot = false;
}

void File::setName(CCString name)
{
	this->name = name;
}

CCString File::getName()
{
	return this->name;
}

void File::setType(int type)
{
	this->type = type;
}

int File::getType()
{
	return this->type;
}

void File::setAdress(int adress)
{
	this->adress = adress;
}

int File::getAdress()
{
	return this->adress;
}

void File::setMemoryLong(int memoryLong)
{
	this->memoryLong = memoryLong;
}

int File::getMemoryLong()
{
	return this->memoryLong;
}

void File::setIsLive(bool isLive)
{
	this->isLive = isLive;
}

bool File::getIsLive()
{
	return isLive;
}

void File::setNum(int num)
{
	this->num = num;
}

int File::getNum()
{
	return this->num;
}

void File::setIsRoot(bool isRoot)
{
	this->isRoot = isRoot;
}

bool File::getIsRoot()
{
	return isRoot;
}

void File::setPath(string fathrePath)
{
	fathrePath = fathrePath + "\\";
	path = fathrePath + name.getCString();
}

string File::getPath()
{
	return this->path;
}

CCString File::getFile()
{
	const char *str1 = name.getCString();
	char *filename;
	memset(filename, '\0', sizeof(filename));
	for (int i = 0; i < strlen(str1); i++)
	{
		filename[i] = str1[i];
	}
	filename = strcat(filename, ".txt");
	freopen(filename, "r", stdin);
	
	char readStr[1000];
	char *essay;
	memset(readStr, '\0', sizeof(readStr));
	memset(essay, '\0', sizeof(essay));
	while (gets_s(readStr) != 0)
	{
		readStr[strlen(readStr)] = '\n';
		essay = strcat(essay, readStr);
	}

	CCString *ccout = CCString::createWithFormat("%s",essay);
	return *ccout;
}
