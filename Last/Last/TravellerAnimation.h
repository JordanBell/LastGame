#pragma once
#include "animationmodule.h"
class TravellerAnimation : public AnimationModule
{
public:
	TravellerAnimation(void) : AnimationModule(XY(3, 4), XY(TILE_SIZE), 3, 5, true) {}
};

