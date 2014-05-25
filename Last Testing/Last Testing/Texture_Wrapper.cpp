#include "Texture_Wrapper.h"
#include "Resources.h"
#include "ToolKit.h"
#include "Renderer_Wrapper.h"

// Player, Door, GridTiles
Texture_Wrapper::Texture_Wrapper(const SSID ssid, const bool staticClip, SDL_Rect* clip)
{
	m_clip = clip;
	LoadSource(ssid);
	m_targetStreamer = NULL;

	if (m_source)
		CreateTextureFromSource(staticClip);
	else
		CreateTextureForStreaming();
}

Texture_Wrapper::~Texture_Wrapper(void)
{
	SDL_FreeSurface(m_source);
	SDL_DestroyTexture(m_texture);
}

void Texture_Wrapper::LoadSource(SSID ssid)
{
	// Set the sprite sheet from the SpriteSheetID
	switch (ssid)
	{
	case SSID_NULL:
		m_source = NULL;
		break;
	case SSID_ENVIRONMENT:
		m_source = Resources::GetEnvironmentImage();
		break;
	case SSID_PLAYER:
		m_source = Resources::GetPlayerImage();
		break;
	case SSID_DOOR:
		m_source = Resources::GetDoorImage();
		break;
	default:
		throw runtime_error("SSID not recognised during Texture construction.");
	}
}

void Texture_Wrapper::CreateTextureFromSource(bool staticClip)
{
	// Create the texture from the entire sprite sheet source
	m_texture = g_renderer->CreateTexture(m_source);

	if (staticClip)
	{
		// Save the clipped texture, delete everything else
		SDL_Texture* clippedTexture = g_renderer->CreateTexture( Dimensions(m_clip->w, m_clip->h),
																SDL_TEXTUREACCESS_STATIC );
		// Render the clip
		g_renderer->RenderToTexture(m_texture, clippedTexture, m_clip);

		// Set the m_texture as the new clip
		m_texture = clippedTexture;

		// Get rid of any source surface
		if (m_source) SDL_FreeSurface(m_source);

		// Nullify pointers related to dynamic images
		m_source = NULL;
		m_clip = NULL;
	}
}

void Texture_Wrapper::CreateTextureForStreaming(void)
{
	// Texture Streamers don't have their own image, but stream images from others
	m_texture = g_renderer->CreateTexture(Dimensions(64, 64), SDL_TEXTUREACCESS_TARGET);
	/*m_texture = g_renderer->CreateTexture(Dimensions(64, 64), 
										 SDL_TEXTUREACCESS_TARGET | 
										 SDL_TEXTUREACCESS_STREAMING);*/
	
	// Render an (eventually transparent) rectangle onto the texture
	SDL_Rect rectangleRect = RectFromXY(XY(), Dimensions(64, 64));
	g_renderer->RenderRectToTexture(m_texture, &rectangleRect, 0x00, 0xFF, 0x00, 0xFF);
}

Dimensions Texture_Wrapper::Size(void) const
{
	Dimensions r_size = Dimensions(0, 0);

	int sizeX = 0;
	int sizeY = 0;

	// Query
	//int result = SDL_QueryTexture(m_texture, 0, 0, (int*)(&r_size.x), (int*)(&r_size.y));
	int result = SDL_QueryTexture(m_texture, 0, 0, &sizeX, &sizeY);

	return Dimensions(sizeX, sizeY);
}

void Texture_Wrapper::RenderToTarget(Coordinates pos) const
{
	if (m_texture != NULL)
	{
		// Render to m_targetStreamer. If m_targetStreamer is NULL, SDL still renders direct to the Window.
		if (m_targetStreamer) RenderToStreamer(pos);
		else				  RenderToWindow(pos);
	}
	else throw runtime_error("Cannot render a NULL texture.");
}

void Texture_Wrapper::RenderToStreamer(Coordinates pos) const
{
	// Get the streamed texture of the target
	SDL_Texture* targetTexture = m_targetStreamer->GetTexture();

	// Render to it
	g_renderer->RenderToTexture(m_texture, targetTexture, m_clip);
}

void Texture_Wrapper::RenderToWindow(Coordinates pos) const
{
	// Create blitting rect using pos and size
	//SDL_Rect textureRect = RectFromXY(pos, Size());

	// Create blitting rect using pos
	SDL_Rect textureRect = RectFromXY(pos, Dimensions());
	g_renderer->RenderToWindow(m_texture, m_clip, &textureRect);
}