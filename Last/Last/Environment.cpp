#include "Environment.h"
#include "Config.h"

Environment* g_environment = nullptr;

Environment::Environment() : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE), 
							 topLayer(true), 
							 middleLayer(false), 
							 bottomLayer(true) {}

void Environment::InitLayers(void)
{
	AddChild(&bottomLayer);
	AddChild(&middleLayer);
	AddChild(&topLayer);
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