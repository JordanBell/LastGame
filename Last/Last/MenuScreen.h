#pragma once
#include "entitycontainer.h"
#include <string>

class MenuManager;

class MenuScreen : public EntityContainer
{
public:
	// Change the Menu. Accessible by children etc.
	void SetMenu(std::string name);

	// Go to the previous menu
	void GoBack(void);

protected:
	MenuScreen(void) 
		: EntityContainer(LOGICAL_SIZE), m_menuManager(nullptr) {}
	~MenuScreen(void);
	
	MenuManager* m_menuManager;
	
	/*
	Update and Render are overridden, so that they update and 
	render only the current menu, as selected by the menu manager.
	*/
	void E_Update(const int delta);
	void E_Render(void);
};

