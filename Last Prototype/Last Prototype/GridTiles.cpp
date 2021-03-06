#include "GridTiles.h"

void EnvironmentTile::SetTileClip(const int index1, const int index2)
{
	SDL_Rect clip = SDL_Rect();
	clip.x = index1 * TILE_SIZE;
	clip.y = index2 * TILE_SIZE;
	clip.w = clip.h = TILE_SIZE;
		
	skin = clip;
}

Door::Door(const int x, const int y) : TileSprite(x, y), open(false), inAnimation(false)
{ 
	max_cycles = numClips*framesPerClip;
	canMoveThrough = open; 
	sprite_sheet = Resources::GetDoorImage();
	blitOffset = XY(0, -TILE_SIZE/2);

	// Initialise the clips
	for (int i = 0; i < numClips; i++)
	{
		SDL_Rect clip;
		clip.x = i*TILE_SIZE;
		clip.y = 0;
		clip.w = TILE_SIZE;
		clip.h = TILE_SIZE*1.5;

		clips[i] = clip;
	}
}

void Door::onInteract(void)
{
	if (!inAnimation)
	{
		open = !open; // Toggle
		if (!open) setMoveThrough(); // If closing, set the door as closed immediately.
		inAnimation = true; // Start the animation
	}
}

void Door::update(const int delta)
{
	if (inAnimation)
	{
		if (open) IncCycle(); // Increment if opening
		else	  DecCycle(); // Decrement if closing

		// If at the end of an animation
		if ((cycle == 0) || (cycle == max_cycles-1))
		{
			inAnimation = false;
			setMoveThrough();
		}
	}
}