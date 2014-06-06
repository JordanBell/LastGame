#pragma once
#include "Button.h"
#include "GameStateManager.h"
#include "ToolKit.h"

/*
A MenuItem is a button component of a Menu entity 
container. This button has an OnClick function that 
can either execute its own code, or access its
MenuManager to switch to another Menu object.
*/
class MenuItem : public Button
{

protected:
	MenuItem(const Coordinates& _pos, const string& text);

	/* Throws logic error if not overridden. 
	Letting this just equal 0 didn't work out, when 
	trying to cast implementations to MenuItem. */
	virtual void OnClick(void) 
		{ throw std::logic_error("Subclasses of MenuItem must override OnClick()."); } 

	// Change color if the mouse is over this item or not
	void OnHoverOver(void);
	void OnHoverOff(void);

	void E_Render(void) { SDL_Rect rect = {pos.x, pos.y, m_boundingBox.w, m_boundingBox.h}; RenderRectToWindow(&rect, 0xFF, 0xFF, 0x00, 0xFF); /*Button::E_Render();*/}

private:
	string m_text;
	static TTF_Font* s_font;

	// Compute the bounding box based on the text
	static SDL_Rect ComputeBoundingBox(const string& text);
};

namespace MenuItems
{
	/***	TITLE SCREEN	***/
	// Create a new game
	class NewGame : public MenuItem {
	public:
		NewGame(Coordinates _pos) : MenuItem(_pos, "New Game") {}
	protected:
		void OnClick(void)
			{ g_manager->SwitchToState(GSID_MAIN); }
	};

	// Exit the program
	class ExitGame : public MenuItem {
	public:
		ExitGame(Coordinates _pos) : MenuItem(_pos, "Exit") {}
	protected:
		void OnClick(void)
			{ g_manager->Quit(); }
	};

	/***	GAME PAUSE MENU		***/
	// Unpause the game, and resume from the Pause Menu
	class Resume : public MenuItem {
	public:
		Resume(Coordinates _pos) : MenuItem(_pos, "Resume") {}
	protected: 
		void OnClick(void)
			{ g_game->Unpause(); }
	};
}
