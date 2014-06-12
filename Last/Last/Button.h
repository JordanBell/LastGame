#pragma once
#include "Entity.h"
#include "EventHandler.h"
class Button : public Entity, public EventHandler
{
public:
	Button(const Coordinates& _pos, SDL_Rect boundingBox, SSID spriteSheetID) 
		: Entity(_pos, Dimensions(), spriteSheetID, BUTTON_FRMT), 
		  m_boundingBox(boundingBox), m_mouseIsOver(false), m_mouseMovement(false) {}

	Button(const Coordinates& _pos, SDL_Rect boundingBox) 
		: Entity(_pos, Dimensions(), BUTTON_FRMT), 
		  m_boundingBox(boundingBox), m_mouseIsOver(false), m_mouseMovement(false) {}

	virtual void OnClick(void) = 0;
	virtual void OnHoverOver(void) {}
	virtual void OnHoverOff(void) {}

	// Check for a click
	void OnEvent(SDL_Event& event);

	// Return whether or not this mouse is over this object, and within its bounding rectangle.
	bool MouseIsOver(void) { return m_mouseIsOver; }

protected:
	SDL_Rect m_boundingBox; // The entity-relative rectangle, within which the mouse is considered "over".

	// Respond to changes to the hovering mouse, save the value of MouseIsOver
	void E_Update(const int delta);

private:
	bool m_mouseMovement;
	bool m_mouseIsOver;

	// Compute whether or not this mouse is over this object, and within its bounding rectangle. Save the value of MouseIsOver
	void m_ComputeMouseOver(void);
};
