#include "Environment.h"
#include "Config.h"

Environment* g_environment = nullptr;

Environment::Environment() : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE), 
							 topLayer(false), 
							 middleLayer(false), 
							 bottomLayer(false) {}

void Environment::InitLayers(void)
{
	AddChild(&topLayer);
	AddChild(&middleLayer);
	AddChild(&bottomLayer);
}

void Environment::E_Update(const int delta)
{
	topLayer.Update(delta);
	middleLayer.Update(delta);
	bottomLayer.Update(delta);
}

void Environment::E_Render(void)
{
	topLayer.Render();
	/*middleLayer.Render();
	bottomLayer.Render();*/
}

list<Entity*>& Environment::GetEntitiesAt(const Coordinates& position, const Layer layer)
{
	switch (layer)
	{
	case TOP_LAYER:
		return topLayer.GetEntitiesAt(position);
	case MIDDLE_LAYER:
		return middleLayer.GetEntitiesAt(position);
	case BOTTOM_LAYER:
		return bottomLayer.GetEntitiesAt(position);
	default:
		throw std::runtime_error("Cannot access undefined Environment layer.");
	}
}