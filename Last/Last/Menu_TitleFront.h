#pragma once
#include "Menu.h"
#include "MenuItem.h"
using namespace MenuItems;

/*
DEPRECATED
*/

class Menu_TitleFront : public Menu
{
public:
	Menu_TitleFront(void);
	~Menu_TitleFront(void);

private:
	// The components of this Menu
	MenuItems::NewGame m_newGame;
	MenuItems::ExitGame m_exit;
};

