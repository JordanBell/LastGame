#pragma once
#include "SDL.h"
#include <iostream>
//#include "Entity.h"
//#include "Texture_Wrapper.h"
#include "Renderer_Wrapper.h"
#include "Config.h"

class Test
{
public:
	Test(SDL_Rect* clip) /*: testImage(SSID_ENVIRONMENT, clip), 
						   testStreamer()*/ {}
	~Test(void) {}

	void InitMembers(void);
	void Run(void);

private:
	//Image testImage;
	//ImageStreamer testStreamer;
};