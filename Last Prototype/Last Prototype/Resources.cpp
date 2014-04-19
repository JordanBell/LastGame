#include "Resources.h"
#include "toolkit.h"
#include "Player.h"
#include "Environment.h"

#include <stdexcept>
Resources* g_resources = NULL;

Resources::Resources(void)
{
	// Load the resouce files using SDL
	m_PlayerSheet =			load_image("playerSheet.png");
	m_EnvironmentImage =	load_image("environment.png");

	// Check for failures.
	if ((m_PlayerSheet		  == NULL)	||
		(m_EnvironmentImage   == NULL)) 
		{
			throw std::runtime_error("Some of the resources failed to initialise");
		}
}

Resources::~Resources(void)
{
	// Free that shit
	SDL_FreeSurface(m_PlayerSheet);
	SDL_FreeSurface(m_EnvironmentImage);
}
