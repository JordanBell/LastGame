#include "TitleMenuScreen.h"
#include "MenuItem.h"
#include "MenuManager.h"

using namespace MenuItems;

TitleMenuScreen::TitleMenuScreen(void)
	: m_background(LOGICAL_SIZE, true)
{
	// Initialise the semi-transparent background rectangle
	SDL_Rect backgroundRect = {0, 0, LOGICAL_SIZE.x, LOGICAL_SIZE.y};
	RenderRectToTexture( m_background.GetTexture(),
						 &backgroundRect,
						 0xFF, 0xFF, 0xFF, 0x00);

	m_background.SetTarget(&m_imageTarget);



	// Initialise the list of menus held within this
	list<Menu*> menuList = list<Menu*>();

	// Front Menu (first seen on start-up)
	Menu* frontMenu = new Menu("front");
		frontMenu->AddChild(
			new NewGame(Coordinates(50, 50)));
		frontMenu->AddChild(
			new Options(Coordinates(50, 100)));
		frontMenu->AddChild(
			new ExitGame(Coordinates(50, 150)));
	menuList.push_back(frontMenu);

	// Options Menu (Graphics, settings, etc.)
	Menu* optionsMenu = new Menu("options");
		optionsMenu->AddChild(
			new FullscreenToggle(Coordinates(50, 50)));
	// etc.
	menuList.push_back(optionsMenu);
	
	m_menuManager = new MenuManager(menuList);
	
	// Test setting the menu by string
	m_menuManager->SetMenu("front");
}

void TitleMenuScreen::E_Render(void)
{
	// Render background texture
	m_background.RenderToTarget(Coordinates(0));

	MenuScreen::E_Render();
}

