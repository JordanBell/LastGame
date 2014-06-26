#include "MenuScreen.h"
#include "MenuManager.h"

MenuScreen::~MenuScreen(void)
{
	 delete m_menuManager;
}

void MenuScreen::SetMenu(std::string name)
{ 
	m_menuManager->SetMenu(name); 
}

void MenuScreen::GoBack(void) 
{ 
	m_menuManager->GoBack();
}

void MenuScreen::E_Update(const int delta) 
{ 
	Menu* currentMenu = m_menuManager->GetCurrentMenu();
	currentMenu->Update(delta);

	// Then render this entity container
	EntityContainer::E_Update(delta); 
}

void MenuScreen::E_Render(void) 
{ 
	Menu* currentMenu = m_menuManager->GetCurrentMenu();
	currentMenu->Render();

	// Then render this entity container
	EntityContainer::E_Render(); 
}
