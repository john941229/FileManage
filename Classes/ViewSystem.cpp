#include "ViewSystem.h"

ViewSystem::ViewSystem()
{
	this->visibleSize = Director::getInstance()->getVisibleSize();
}

ViewSystem::~ViewSystem()
{

}

Size ViewSystem::getVisibleSize()
{
	return this->visibleSize;
}

SystemFile* ViewSystem::getNowFile()
{
	return this->nowFile;
}

void ViewSystem::setNowFile(SystemFile* nowFile)
{
	this->nowFile = nowFile;
}

SystemFile* ViewSystem::getFromFile()
{
	return this->fromFile;
}

void ViewSystem::setFromFile(SystemFile* fromFile)
{
	this->fromFile = fromFile;
}