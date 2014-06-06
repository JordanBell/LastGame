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
};