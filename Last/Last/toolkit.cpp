#include "ToolKit.h"
#include <math.h>
#include "Config.h"
#include "Renderer_Wrapper.h"
#include "SDL.h"
#include "SDL_image.h"

Window* g_window = nullptr;
Renderer* g_renderer = nullptr;

SDL_Rect RectFromXY(const Coordinates& pos, const Dimensions& dims) 
{ 
	SDL_Rect r_rect = {pos.x, pos.y, 
					   dims.x, dims.y}; 
	return r_rect; 
}

float MyOwnGoshDarnMinFunction(float f1, float f2) { return (f1 > f2) ? f1 : f2; }
float MyOwnGoshDarnMaxFunction(float f1, float f2) { return (f1 > f2) ? f2 : f1; }

#define min(a,b) (a < b) ? a : b
#define max(a,b) (a > b) ? a : b

SDL_Rect MyOwnGoshDarnRectIntersectionFunction(SDL_Rect* r1, SDL_Rect* r2)
{
	Directions<float> r1Bounds = Directions<float>(*r1);
	Directions<float> r2Bounds = Directions<float>(*r2);
	Directions<float> returnDistances = Directions<float>(0, 0, 0, 0);
	
	/*returnDistances.top = MyOwnGoshDarnMaxFunction(r1Bounds.top, r2Bounds.top);
	returnDistances.bottom = MyOwnGoshDarnMinFunction(r1Bounds.bottom, r2Bounds.bottom);
	returnDistances.left = MyOwnGoshDarnMaxFunction(r1Bounds.left, r2Bounds.left);
	returnDistances.right = MyOwnGoshDarnMinFunction(r1Bounds.right, r2Bounds.right);*/
	
	returnDistances.top = max(r1Bounds.top, r2Bounds.top);
	returnDistances.bottom = min(r1Bounds.bottom, r2Bounds.bottom);
	returnDistances.left = max(r1Bounds.left, r2Bounds.left);
	returnDistances.right = min(r1Bounds.right, r2Bounds.right);

	bool intersects = SDL_HasIntersection(r1, r2);
	if (!intersects) 
	{
		SDL_Rect errorRect = {-1, -1, -1, -1};
		return errorRect;
	}

	SDL_Rect r_rect = { returnDistances.left, returnDistances.top, 
						returnDistances.right - returnDistances.left,
						returnDistances.bottom - returnDistances.top};

	return r_rect;
}

bool RectIsWithin(SDL_Rect* subject, SDL_Rect* target)
{
	SDL_Rect intersectionRect = MyOwnGoshDarnRectIntersectionFunction(subject, target);

	// If the intersection rect is smaller than the smaller rect, some is being cut off.
	if (intersectionRect.w == -1)
		printf("Breakpoint: No Intersection!\n");
	if ( !SDL_RectEquals(subject, &intersectionRect) )
		printf("Rect not within.\n");
	return SDL_RectEquals(subject, &intersectionRect);
}

bool RectIsWithin(SDL_Rect* subject, SDL_Texture* target)
{
	// Find the rect of the target's size
	Dimensions destSize = Dimensions(0);
	int sizeX = 777, sizeY = 0;
	int successInt = SDL_QueryTexture(target, 0, 0, &sizeX, &sizeY);
	if (successInt != 0) {
		printf("%s\n", SDL_GetError());
		throw std::runtime_error("Query Failed explicitly...");
	}
	else if (sizeX == 777)
		throw std::runtime_error("Query didn't query, failed implicitly...");

	// Delegate the check using that rect
	SDL_Rect destinationBounds = {0, 0, sizeX, sizeY};
	return RectIsWithin(subject, &destinationBounds);
}

