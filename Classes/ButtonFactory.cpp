#include "ButtonFactory.h"

ButtonFactory::ButtonFactory()
{
}

ButtonFactory::~ButtonFactory()
{
}

MyButton* ButtonFactory::createButton(int type, Menu* menuButton, int positionX, int positionY)
{
	MyButton* button = NULL;
	switch (type)
	{
		case 0:
		{
			button = new BackOffButton(menuButton, positionX, positionY);
			break;
		}
		case 1:
		{
			button = new ClearButton(menuButton, positionX, positionY);
			break;
		}
		case 2:
		{
			button = new CreateDocumentButton(menuButton, positionX, positionY);
			break;
		}
		case 3:
		{
			button = new CreateFolderButton(menuButton, positionX, positionY);
			break;
		}
		case 4:
		{
			button = new DeleteFolderButton(menuButton, positionX, positionY);
			break;
		}
		case 5:
		{
			button = new DeleteDocumentButton(menuButton, positionX, positionY);
			break;
		}
		case 6:
		{
			button = new EnterFolderButton(menuButton, positionX, positionY);
			break;
		}
		case 7:
		{
			button = new EnterDocumentButton(menuButton, positionX, positionY);
			break;
		}
		default:
			break;
	}
	return button;
}