#pragma once
#include <cocos2d.h>
#include "SystemFile.h"

USING_NS_CC;
using namespace std;

class ViewSystem
{
private:
	// �����������ļ�
	static SystemFile* nowFile;
	// ���ĸ��ļ������
	static SystemFile* fromFile;
public:
	ViewSystem();
	~ViewSystem();
	static Size visibleSize;
	SystemFile* getNowFile();
	void setNowFile(SystemFile* nowFile);
	SystemFile* getFromFile();
	void setFromFile(SystemFile* fromFile);
	static void createMySelf();
};