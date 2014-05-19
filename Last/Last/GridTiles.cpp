#include "GridTiles.h"

void EnvironmentTile::SetTileClip(const int index1, const int index2)
{
	SDL_Rect clip = SDL_Rect();
	clip.x = index1 * TILE_SIZE;
	clip.y = index2 * TILE_SIZE;
	clip.w = clip.h = TILE_SIZE;
		
	m_skin = clip;
}