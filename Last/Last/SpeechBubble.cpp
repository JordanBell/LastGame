#include "SpeechBubble.h"


SpeechBubble::SpeechBubble(const Coordinates& _pos, const string phrase) 
	: Entity(_pos, 0, SSID_NULL, TEXT_FRMT)
{
	InitText(phrase);

	// Fit the speechbubble around the text
	const Dimensions textSize = m_text->GetImage().Size();
	Dimensions bubbleSize = textSize / TILE_SIZE; // In terms of tiles
	bubbleSize.RoundToInt(); // Round down
	bubbleSize++; // Increment for margin.

	int textTileWidth = bubbleSize.x;
	int textTileHeight = bubbleSize.y;

	// Construct the speechbubble image
	Dimensions imageSize = Dimensions((textTileWidth +1)*TILE_SIZE,
									  (textTileHeight+1)*TILE_SIZE);

	// Debug grid
	ImageTarget* speechBubble = new ImageTarget(imageSize, true);
	for (int i = 0; i <= textTileWidth; i++) // Note: Inclusive of textTile size bounds, as a minimum size speech bubble will be 2x2 tiles (four corners)
	{
		for (int j = 0; j <= textTileHeight; j++)
		{
			SDL_Rect outlineRect = {i*TILE_SIZE, j*TILE_SIZE, TILE_SIZE, TILE_SIZE};
			SDL_Rect inlineRect = {i*TILE_SIZE+1, j*TILE_SIZE+1, TILE_SIZE-2, TILE_SIZE-2};

			RenderRectToTexture(speechBubble->GetTexture(), &outlineRect, 0x00, 0x00, 0x00, 0xFF);
			RenderRectToTexture(speechBubble->GetTexture(), &inlineRect, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}

	// The hard-coded clip rects
	/*int a = TILE_SIZE;
	SDL_Rect topLeft = {0, 0, a, a};
	SDL_Rect topMiddle = {a, 0, a, a};
	SDL_Rect topRight = {2*a, 0, a, a};
	SDL_Rect top[3] = {topLeft, topMiddle, topRight};

	SDL_Rect midLeft = {0, a, a, a};
	SDL_Rect center = {a, a, a, a};
	SDL_Rect midRight = {2*a, a, a, a};
	SDL_Rect mid[3] = {midLeft, center, midRight};

	SDL_Rect bottomLeft = {0, 2*a, a, a};
	SDL_Rect bottomMiddle = {a, 2*a, a, a};
	SDL_Rect bottomRight = {2*a, 2*a, a, a};
	SDL_Rect bottom[3] = {bottomLeft, bottomMiddle, bottomRight};
	SDL_Rect* clips[3] = {top, mid, bottom};*/

	int count = 0;

	// For each tile in the bubble
	if (ENABLE_SPEECH_BUBBLES) 
		printf("\nNew Speech saying, '%s'.\n", phrase.c_str());
	//Image changingClipImage = Image(SSID_SPEECH, nullptr, false);
	for (int i = 0; i <= textTileWidth; i++) // Note: Inclusive of textTile size bounds, as a minimum size speech bubble will be 2x2 tiles (four corners)
	{
		for (int j = 0; j <= textTileHeight; j++)
		{
			count++;

			int horiIndex;
			int vertIndex;
			
			if (i == 0)					 horiIndex = 0; // Left
			else if (i == textTileWidth) horiIndex = 2; // Right
			else						 horiIndex = 1; // Mid
			//horiIndex = rand() % 3; // Manual override for testing
			//horiIndex = 1; // Manual override for testing
			
			if (j == 0)					  vertIndex = 0; // Top
			else if (j == textTileHeight) vertIndex = 2; // Bottom
			else						  vertIndex = 1; // Mid
			//vertIndex = rand() % 3; // Manual override for testing
			//vertIndex = 1; // Manual override for testing

			int a = TILE_SIZE;
			SDL_Rect smartClip = {horiIndex*a, vertIndex*a, a, a};

			// Determine the sprite sheet segment to use
			if (ENABLE_SPEECH_BUBBLES) 
				printf("At (%d, %d):\n\tHori: %d, Vert: %d\n", i, j, horiIndex, vertIndex);
			SDL_Rect* segmentClip = &smartClip;
			//SDL_Rect* segmentClip = &clips[vertIndex][horiIndex];
			//SDL_Rect* segmentClip = &center;
			Coordinates segmentPos = Coordinates(i*TILE_SIZE, j*TILE_SIZE);
			Image imageSegment = Image(SSID_SPEECH, segmentClip, true);
			//changingClipImage.SetClip(segmentClip);

			// Slap this segment onto the main image
			imageSegment.SetTarget( speechBubble );
			imageSegment.RenderToTarget( segmentPos );
			/*changingClipImage.SetTarget( speechBubble );
			changingClipImage.RenderToTarget( segmentPos );*/
		}
	}

	Coordinates bubbleCenter = speechBubble->Size()/2;
	m_text->CenterAround(bubbleCenter);
	m_text->pos.x++;
	m_text->pos.RoundToInt(); // Align the pixels to avoid decimal blur
	m_text->GetImage().SetTarget(speechBubble);
	m_text->GetImage().RenderToTarget(m_text->pos);

	// Set this entity's image to that of the bubble
	SetImage(*speechBubble);
}

void SpeechBubble::InitText(const string phrase)
{
	// Create a new text object with the phrase
	TTF_Font* font = TTF_OpenFont("joystix monospace.ttf", s_textSize);

	SDL_Color black = {0,0,0};
	int* pixelWrap = new int((s_maxWidth-1)*TILE_SIZE);
	//int* pixelWrap = new int((s_maxWidth)*TILE_SIZE);
	Text* text = new Text( phrase, font, black, pixelWrap );

	// Point the member unique_ptr to that object
	m_text = unique_ptr<Text>(text);
}
