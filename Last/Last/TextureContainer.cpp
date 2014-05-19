#include "TextureContainer.h"

TextureContainer::~TextureContainer(void)
{
	// Free children
	int numChildren = children.size();
	for (int i = 0; i < numChildren; i++)
		children.pop_back();

	// Free texture
	SDL_DestroyTexture(m_container);
}
