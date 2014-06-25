#include "MenuManager.h"

void MenuManager::AddMenu(Menu* menu) 
{ 
	// Set menu as default, if currentMenu not set.
	if (!m_currentMenu)
		SetMenu(menu);

	// Add the menu to the list
	m_menus.emplace_back( menu );
}


Menu* MenuManager::GetMenuByName(string menuName)
{
	for (auto& menu : m_menus)
	{
		if (menu->name == menuName)
			return menu.get();
	}

	throw std::runtime_error("Could not recognise the menu name among the menus linked to this MenuManager.");
}

void MenuManager::SetMenu(Menu* menu)
{
	/*** Call any animations from and to the exchanging menus ***/
	m_currentMenu = menu;

}
