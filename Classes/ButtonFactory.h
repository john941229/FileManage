#pragma once
#include <cocos2d.h>
#include "BackOffButton.h"
#include "ClearButton.h"
#include "CreateDocumentButton.h"
#include "CreateFolderButton.h"
#include "DeleteDocumentButton.h"
#include "DeleteFolderButton.h"
#include "EnterDocumentButton.h"
#include "EnterFolderButton.h"
#include "MyButton.h"

class  ButtonFactory
{
private:
	MyButton* createButton(int type, Menu* menuButton, int positionX, int positionY);
public:
	ButtonFactory();
	~ButtonFactory();
};