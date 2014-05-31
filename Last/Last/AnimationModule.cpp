#include "AnimationModule.h"

/*
Iterates through and provides rectangular clips for given sprite sheet information.
Main method: GetClip(), which returns the currently selected rectangle clip.
*/
AnimationModule::AnimationModule(Dimensions spriteSheetDimensions, // Width and Height of the sprite sheet this is providing clips for
								 Dimensions clipSize,		// The Width and Height of the desired clips
								 int numClipCycles, // Number of different clips in the cyclical direction
								 int framesPerClip, // Number of frames spent on each clip
								 bool backAndForth) // If set as true, cycles iterate back and forth between MIN and MAX
		: m_dimensions(spriteSheetDimensions), m_clipSize(clipSize), m_iterator(numClipCycles*framesPerClip, backAndForth), m_framesPerClip(framesPerClip)
{
	// Set the clip arrays
	int width =  (int)spriteSheetDimensions.x;
	int height = (int)spriteSheetDimensions.y;
	
	// Initialise the size of the row arrays
	m_clips = new SDL_Rect*[width];

	for (int i = 0; i < width; i++)
	{
		// Initialise the size of the column array
		m_clips[i] = new SDL_Rect[height];

		// Set the clips at this column
		for (int j = 0; j < height; j++)
		{
			SDL_Rect clip;
			clip.x = i*clipSize.x;
			clip.y = j*clipSize.y;
			clip.w = clipSize.x;
			clip.h = clipSize.y;

			m_clips[i][j] = clip;
		}
	}
}

AnimationModule::~AnimationModule(void)
{
	delete[]m_clips;
}

void AnimationModule::OverrideCycle(int newCycle) 
{ 
	// Delegate, with respect to the number of frames per clip
	m_iterator.OverrideCycle(newCycle*m_framesPerClip); 
}


SDL_Rect* AnimationModule::GetClip(E_Direction direction)
{
	// Get the iterator index
	int cycle = m_iterator.m_cycle;

	// Get the clip at that index, in the given direction
	return &m_clips[cycle/m_framesPerClip][direction];
}