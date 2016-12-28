#include "FileFactory.h"

FileFactory::FileFactory()
{

}

FileFactory::~FileFactory()
{

}

SystemFile* FileFactory::createFile(int type)
{
	SystemFile* systemFile = NULL;
	switch (type)
	{
		case 0:
		{
			systemFile = new Folder();
			break;
		}
		case 1:
		{
			systemFile = new Document();
			break;
		}
		default:
			break;
	}
	return systemFile;
}