#include "Tiles.h"
#include "Config.h"

SDL_Rect Tile::GetTileClip(const Coordinates& tileIndex)
{
	SDL_Rect clip = SDL_Rect();
	clip.x = tileIndex.x * TILE_SIZE;
	clip.y = tileIndex.y * TILE_SIZE;
	clip.w = clip.h = TILE_SIZE;
		
	return clip;
}