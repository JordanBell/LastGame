#pragma once
#include "Menu.h"
#include <list>
#include <string>
using namespace std;

class MenuManager
{
public:
	MenuManager(list<Menu*> menus) 
		: m_menus(menus) { SetMenu( menus.front() ); }
	MenuManager() : m_currentMenu(nullptr) {}
	virtual ~MenuManager(void) { 
		/*for (Menu* m : m_menus)
			delete m;*/
	}

	// Get the menu that the manager is pointing to.
	Menu* GetCurrentMenu(void) { return m_currentMenu; }
	
	// Set the current menu based on its name.
	void SetMenu(string menuName) { SetMenu( GetMenuByName(menuName) ); }
	// Add a menu to the list of menus managed by this object.
	void AddMenu(Menu* menu) { m_menus.push_back(menu); }

	// Render the current menu.
	void RenderMenu(void) { m_currentMenu->Render(); }

private:
	list<Menu*> m_menus; // The list of menus managed by this object
	Menu* m_currentMenu; // A pointer to the menu in current use

	void SetMenu(Menu* menu); // Set the menu based on the menu argument
	Menu* GetMenuByName(string menuName);
};
