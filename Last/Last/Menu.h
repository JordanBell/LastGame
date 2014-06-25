#pragma once
#include "EntityContainer.h"
#include "MenuItem.h"
#include <string>

/*
A menu is the entity container that holds 
all of the menu items - buttons in the menu.
*/
class Menu : public EntityContainer
{
public:
	string name;

	Menu(std::string _name);
	
	// Make sure the children are Menu items
	void AddChild(MenuItem* child) { EntityContainer::AddChild(child); }

	// Parent Menu
	void SetParentMenu( Menu* parentMenu ) { m_parentMenu = parentMenu; }
	Menu* GetParentMenu(void) { return m_parentMenu; }

private:
	Menu* m_parentMenu;
};