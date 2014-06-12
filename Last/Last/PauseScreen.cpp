#include "PauseScreen.h"
#include "ToolKit.h"
#include "MenuManager.h"
#include "MenuItem.h"
using namespace MenuItems;

PauseScreen::PauseScreen(void) 
	: m_transparentBlack(LOGICAL_SIZE, true), m_active(false)
{
	// Initialise the semi-transparent background rectangle
	SDL_Rect backgroundRect = {0, 0, LOGICAL_SIZE.x, LOGICAL_SIZE.y};
	RenderRectToTexture( m_transparentBlack.GetTexture(),
						 &backgroundRect,
						 0x00, 0x00, 0x00, 0xEE);

	m_transparentBlack.SetTarget(&m_imageTarget);



	// Initialise the list of menus held within this
	list<Menu*> menuList = list<Menu*>();

	// Front Menu (first seen on start-up)
	Menu* frontMenu = new Menu("front");
		frontMenu->AddChild(
			new Resume(Coordinates(50, 50)));
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


void PauseScreen::Open(void)
{
	// Make entities visible
	m_active = true;
}


void PauseScreen::Close(void)
{
	// Hide entities
	m_active = false;
}

void PauseScreen::E_Render(void)
{
	if (m_active)
	{
		// Render background texture
		m_transparentBlack.RenderToTarget(Coordinates(0));

		// Render entities
		MenuScreen::E_Render();
	}
}
