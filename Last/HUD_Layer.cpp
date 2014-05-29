#include "HUD_Layer.h"

HUD_Layer* UI_HUD = NULL;

void HUD_Layer::InitChildren(void)
{
	AddChild(UI_Fatigue);
	AddChild(UI_Loneliness);
	AddChild(UI_Insanity);
	AddChild(UI_Fear);
}