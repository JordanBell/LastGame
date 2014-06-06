#include "MenuManager.h"

Menu* MenuManager::GetMenuByName(string menuName)
{
	for (Menu* m : m_menus)
		if (m->name == menuName)
			return m;

	throw std::runtime_error("Could not recognise the menu name among the menus linked to this MenuManager.");
}

void MenuManager::SetMenu(Menu* menu)
{
	/*** Call any animations from and to the exchanging menus ***/
	m_currentMenu = menu;

}
