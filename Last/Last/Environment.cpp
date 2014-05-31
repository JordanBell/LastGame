#include "Environment.h"
#include "Config.h"
#include "Player.h" // Initialising g_player
#include "WorldBuilder.h" // Building the world

Environment* g_environment = nullptr;

void Environment::Initialise(void)
{
	AddChild(&bottomLayer);
	AddChild(&middleLayer);
	AddChild(&topLayer);
	
	WorldBuilder::build();
}

list<Entity*>& Environment::GetEntitiesAt(const Coordinates& position, const Layer layer)
{
	switch (layer)
	{
	case TOP_LAYER:
		return topLayer.GetEntitiesAt(position);
		break;
	case MIDDLE_LAYER:
		return middleLayer.GetEntitiesAt(position);
		break;
	case BOTTOM_LAYER:
		return bottomLayer.GetEntitiesAt(position);
		break;
	default:
		throw std::runtime_error("Cannot access undefined Environment layer.");
	}
}