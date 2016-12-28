#include "ButtonFactory.h"

ButtonFactory::ButtonFactory()
{
}

ButtonFactory::~ButtonFactory()
{
}

MyButton* ButtonFactory::createButton(int type, ViewLayer* viewLayer, Menu* menuButton, int positionX, int positionY)
{
	MyButton* button = NULL;
	switch (type)
	{
		case 0:
		{
			button = new BackOffButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 1:
		{
			button = new ClearButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 2:
		{
			button = new CreateDocumentButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 3:
		{
			button = new CreateFolderButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 4:
		{
			button = new DeleteFolderButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 5:
		{
			button = new DeleteDocumentButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 6:
		{
			button = new EnterFolderButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		case 7:
		{
			button = new EnterDocumentButton(viewLayer, menuButton, positionX, positionY);
			break;
		}
		default:
			break;
	}
	return button;
}