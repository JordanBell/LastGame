#include "Button.h"

void Button::E_Update(const int delta)
{
	// Only respond to mouse if it has moved since last check.
	if (m_mouseMovement)
	{
		// Keep the old mouseIsOver bool value, to check for a change
		bool oldBool = m_mouseIsOver;

		// Update the mouseIsOver bool
		m_ComputeMouseOver();

		bool hasChanged = (oldBool != m_mouseIsOver);

		// Only respond to the mouse hovering over or off, if there was a change
		if (hasChanged) {
			if (m_mouseIsOver) OnHoverOver();
			else			   OnHoverOff();
		}
	}

	// Reset to false default until set as true by new event.
	m_mouseMovement = false;
}

void Button::OnEvent(SDL_Event& event)
{
	// Save whether or not there was mouse movement.
	if (event.type == SDL_MOUSEMOTION) m_mouseMovement = true;

	// The button is clicked if it's a mouseDown event, and the mouse is over this button
	if ((event.type == SDL_MOUSEBUTTONDOWN) && m_mouseIsOver)
		OnClick();
}


void Button::m_ComputeMouseOver(void)
{
	// Get the mouse position
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	// Determine the absolute positon of the bounding box
	Coordinates absPos = GetAbsolutePos();
	SDL_Rect absoluteBox = { absPos.x + m_boundingBox.x, 
							 absPos.y + m_boundingBox.y,
							 m_boundingBox.w, m_boundingBox.h };

	// Are they within the bounds?
	m_mouseIsOver = true;

	Directions<float> rectBounds = Directions<float>(absoluteBox);

	// Cases that disprove
	if (mouseY < rectBounds.top) { 
		m_mouseIsOver = false; 
		return;
	}
	if (mouseY > rectBounds.bottom) {
		m_mouseIsOver = false; 
		return;
	}
	if (mouseX < rectBounds.left) {
		m_mouseIsOver = false; 
		return;
	}
	if (mouseX > rectBounds.right) {
		m_mouseIsOver = false; 
		return;
	}
}
