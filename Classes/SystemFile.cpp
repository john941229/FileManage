#include "SystemFile.h"

SystemFile::SystemFile()
{
}

SystemFile::~SystemFile()
{
}

void SystemFile::setType(int type)
{
	this->type = type;
}

int SystemFile::getType()
{
	return this->type;
}

void SystemFile::setName(CCString* name)
{
	this->name = name;
}

CCString* SystemFile::getName()
{
	return this->name;
}

void SystemFile::setIsLive(bool isLive)
{
	this->isLive = isLive;
}

bool SystemFile::getIsLive()
{
	return isLive;
}

void SystemFile::setPath(string fathrePath)
{
	fathrePath = fathrePath + "\\";
	path = fathrePath + name->getCString();
}

string SystemFile::getPath()
{
	return this->path;
}

void SystemFile::setHeadIndex(int headIndex)
{
	this->headIndex = headIndex;
}

int SystemFile::getHeadIndex()
{
	return this->headIndex;
}

void SystemFile::deleteSelf()
{

}

void SystemFile::setIsRoot(bool isRoot)
{
	this->isRoot = isRoot;
}

bool SystemFile::getIsRoot()
{
	return isRoot;
}
