#include "freeMemory.h"


freeMemory::freeMemory()
{
}


freeMemory::~freeMemory()
{
}


freeMemory::freeMemory(int start, int l, int type)
{
	_start = start;
	_long = l;
	_type = type;
}

int freeMemory::getLong()
{
	return _long;
}

int freeMemory::getStart()
{
	return _start;
}

int freeMemory::getType()
{
	return _type;
}

void freeMemory::setStart(int start)
{
	_start = start;
}

void freeMemory::setLong(int l)
{
	_long = l;
}

void freeMemory::setType(int type)
{
	_type = type;
}