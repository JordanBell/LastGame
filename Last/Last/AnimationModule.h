#pragma once
#include "AnimationIterator.h"
#include "Tools.h"
#include "SDL.h"

/* 
Handles animation for an Entity:
	* Frames per clip
	* 2D sprite sheets
	* Animation cycle iteration
The UpdateModule function is automatically called by the 
entity linked with this module, right before rendering.

Abstract function Update() will only be called when the AnimationModule is on 
*/
class AnimationModule
{
public:
	AnimationModule(Dimensions spriteSheetDimensions, Dimensions clipSize, int maxCycles, int framesPerClip = 1, bool backAndForth = false);
	virtual ~AnimationModule(void);

	// Called by Entity only, updates the animation if turned on
	void UpdateModule(void) { if (on) Update(); }

	SDL_Rect* GetClip(E_Direction direction = UP);
	bool IsAnimating(void) { return on; }
	void Start(void) { on = true; m_iterator.TurnOn(); }
	void Stop(void)  { on = false; m_iterator.TurnOff(); }

protected:
	AnimationIterator m_iterator;
	bool on;

	virtual void Update() { m_iterator.Inc(); };

private:
	SDL_Rect** m_clips;
	Dimensions m_dimensions;
	Dimensions m_clipSize;
	int m_framesPerClip;
};