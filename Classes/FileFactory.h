#pragma once
#include "Document.h"
#include "Folder.h"
#include "SystemFile.h"

class FileFactory
{
public:
	FileFactory();
	~FileFactory();
public:
	SystemFile* createFile(int type);
};