#include "Texture_Wrapper.h"
#include "Resources.h"
#include "ToolKit.h"
#include "Renderer_Wrapper.h"

// Player, Door, GridTiles
Texture_Wrapper::Texture_Wrapper(const SSID ssid, SDL_Rect* clip, const bool staticClip) : m_clip(clip), m_staticClip(staticClip), m_target(NULL)
{
	if (ssid == SSID_NULL)
		CreateTextureForTargetting();
	else
		CreateTextureFromFile(ssid);

	if (m_staticClip && m_clip) ClipTexture();
}

TextureTarget::TextureTarget(bool staticImage) : Texture_Wrapper(SSID_NULL, NULL, staticImage) 
{ 
	if (!staticImage) g_renderer->AddTarget(this); 
}

Texture_Wrapper::~Texture_Wrapper(void)
{
	SDL_DestroyTexture(m_texture);
}

void Texture_Wrapper::CreateTextureFromFile(SSID ssid)
{
	// Set the sprite sheet from the SpriteSheetID
	switch (ssid)
	{
	case SSID_NULL:
		m_texture = NULL;
		break;
	case SSID_ENVIRONMENT:
		m_texture = Resources::GetEnvironmentImage();
		break;
	case SSID_PLAYER:
		m_texture = Resources::GetPlayerImage();
		break;
	case SSID_DOOR:
		m_texture = Resources::GetDoorImage();
		break;
	case SSID_STATUS:
		m_texture = Resources::GetStatusImage();
		break;
	default:
		throw runtime_error("SSID not recognised during Texture construction.");
	}
}

void Texture_Wrapper::ClipTexture(void)
{
	// Check for a stupid clip
	if ((m_clip->w== 0) || (m_clip->h == 0)) {
		throw std::runtime_error("Cannot pass a clip with width or height as 0");
	}

	// Save the clipped texture, delete everything else
	SDL_Texture* clippedTexture = CreateTexture( Dimensions(m_clip->w, m_clip->h),
															SDL_TEXTUREACCESS_TARGET);

	// Render the clip from the whole sprite sheet held in m_texture
	RenderTextureToTexture(m_texture, clippedTexture, m_clip);

	// Set the new clip as the main texture, m_texture
	m_texture = clippedTexture;

	// Nullify clip pointer
	m_clip = NULL;
}

void Texture_Wrapper::CreateTextureForTargetting(void)
{
	// Texture Streamers don't have their own image, but stream images from others
	m_texture = CreateTexture(Dimensions(16*TILE_SIZE, 10*TILE_SIZE), SDL_TEXTUREACCESS_TARGET);
}

Dimensions Texture_Wrapper::Size(void) const
{
	Dimensions r_size = Dimensions(0, 0);

	int sizeX = 0;
	int sizeY = 0;

	if (m_clip)
	{
		sizeX = m_clip->w;
		sizeY = m_clip->h;
	}
	else
	{
		// Query
		int result = SDL_QueryTexture(m_texture, 0, 0, &sizeX, &sizeY);
	}

	return Dimensions(sizeX, sizeY);
}

void Texture_Wrapper::Clear(void)
{
	SDL_Rect alphaWashRect = {0, 0, Size().x, Size().y};
	RenderRectToTexture(m_texture, &alphaWashRect, 0x00, 0x00, 0x00, 0x00);
}

void Texture_Wrapper::RenderToTarget(Coordinates pos) const
{
	if (m_texture != NULL)
	{
		// Render to m_target. If m_target is NULL, SDL still renders direct to the Window.
		if (m_target) RenderToTexture(pos);
		else		  RenderToWindow(pos);
	}
	else throw runtime_error("Cannot render a NULL texture.");
}

void Texture_Wrapper::RenderToTexture(Coordinates pos) const
{
	// Get the streamed texture of the target
	SDL_Texture* targetTexture = m_target->GetTexture();

	// Create blitting rect using pos and size
	SDL_Rect textureRect = RectFromXY(pos, Size());

	// Render to it
	RenderTextureToTexture(m_texture, targetTexture, m_clip, &textureRect);
}

void Texture_Wrapper::RenderToWindow(Coordinates pos) const
{
	// Create blitting rect using pos and size
	SDL_Rect textureRect = RectFromXY(pos, Size());
	//SDL_Rect textureRect = RectFromXY(pos, Dimensions(TILE_SIZE));
	RenderTextureToWindow(m_texture, m_clip, &textureRect);
}