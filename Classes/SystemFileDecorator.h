#pragma once
#include <cocos2d.h>
#include "SystemFile.h"

class SystemFileDecorator
{
private:
	SystemFile* systemFile;
public:
	SystemFileDecorator(SystemFile* systemFile);
	~SystemFileDecorator();
	// ���name�Ƿ��Ƕ��ӽڵ������(������һ�����ӽڵ���ͬ��)
	bool checkName(CCString* name);
	// Ѱ��ϵͳ�е��ڴ����ʿ���λ��
	int findAdress(int size);
};