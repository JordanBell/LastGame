#pragma once
#include "entitycontainer.h"
#include "UI_Status.h"
#include "ToolKit.h"

/*
EntityContainer containing the HUD components - UI_Statuses that show information for:
	* Loneliness
	* Fear
	* Insanity
	* Fatigue
*/
class HUD_Layer : public EntityContainer
{
public:
	HUD_Layer(void) 
		: EntityContainer(GetLogicalSize(), Coordinates()) {}

	// Add the four UI_Statuses as children
	void InitChildren(void);

	// Make sure the added child is a UI_Status
	void AddChild(UI_Status* child) { EntityContainer::AddChild(child); }
};

extern HUD_Layer* UI_HUD;