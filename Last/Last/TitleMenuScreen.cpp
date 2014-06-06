#include "TitleMenuScreen.h"
#include "MenuItem.h"
#include "MenuManager.h"

using namespace MenuItems;

TitleMenuScreen::TitleMenuScreen(void)
{
	// Initialise the list of menus held within this
	list<Menu*> menuList = list<Menu*>();

	// Front Menu (first seen on start-up)
	Menu* frontMenu = new Menu("front");
		frontMenu->AddChild(
			new NewGame(Coordinates(50, 50)));
		frontMenu->AddChild(
			new ExitGame(Coordinates(50, 150)));
	menuList.push_back(frontMenu);

	// Options Menu (Graphics, settings, etc.)
	//Menu* optionsMenu = new Menu("options");
	// etc.
	//menuList.push_back(optionsMenu);
	
	m_menuManager = new MenuManager(menuList);
}
