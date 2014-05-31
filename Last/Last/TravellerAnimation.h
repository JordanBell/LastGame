#pragma once
#include "AnimationModule.h"
#include "Config.h"

class TravellerAnimation : public AnimationModule
{
public:
	TravellerAnimation(void) 
		: AnimationModule(Dimensions(3, 4), Dimensions(32, 36), 3, 3, true) {}
};