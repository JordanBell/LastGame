#include "Menu.h"

Menu::Menu(std::string _name) 
		: EntityContainer(LOGICAL_SIZE), name(_name), m_parentMenu(nullptr)
{ 
	/* Determine the position of this 
	menu by the nature of its contents. */ 
}