#pragma once
#include "AnimationModule.h"
#include "Config.h"

class TravellerAnimation : public AnimationModule
{
public:
	TravellerAnimation(void) : AnimationModule(Dimensions(3, 4), Dimensions(TILE_SIZE), 3, 5, true) {}
};

