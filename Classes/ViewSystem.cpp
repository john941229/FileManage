#include "ViewSystem.h"

ViewSystem::ViewSystem()
{
}

ViewSystem::~ViewSystem()
{

}

void ViewSystem::createMySelf()
{
	visibleSize = Director::getInstance()->getVisibleSize();
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