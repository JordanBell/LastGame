#include "Texture_Wrapper.h"
#include "Resources.h"
#include "ToolKit.h"
#include "Renderer_Wrapper.h"

Texture_Wrapper::Texture_Wrapper(const SSID ssid, SDL_Rect* clip, const bool staticClip) 
	: m_clip(clip), m_staticClip(staticClip), m_target(nullptr)
{
	// Create the texture, based on its SSID. If SSID_NULL, do not load a texture image.
	DefineTextureFromFile(ssid);

	// If it's a static clip, and only a section of the sprite sheet is to be used, Clip the Texture (permanently). 
	if (m_staticClip && m_clip) ClipTexture();
	else if ((!m_clip) && (m_texture))
	{
		// If no clip, initialise m_size using loaded texture size
		SDL_QueryTexture(m_texture, 0, 0, (int*)&m_size.x, (int*)&m_size.y);
	}
}

void Texture_Wrapper::DefineTextureFromFile(SSID ssid)
{
	// Set the sprite sheet via the SpriteSheetID
	switch (ssid)
	{
	case SSID_NULL:
		m_texture = nullptr;
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

void Texture_Wrapper::SetClip(SDL_Rect* newClip) 
{ 
	if (!m_staticClip) 
	{
		m_clip = newClip; 
		m_size = Dimensions(m_clip->w, m_clip->h);
	}
	else throw std::runtime_error("Cannot change the clip of a static texture"); 
}


void Texture_Wrapper::ClipTexture(void)
{
	// Check for a stupid clip
	if ((m_clip->w== 0) || (m_clip->h == 0)) {
		throw std::runtime_error("Cannot pass a clip with width or height as 0");
	}

	// Create a new texture, with a new size, to become the clipped copy.
	SDL_Texture* clippedTexture = CreateTexture( Dimensions(m_clip->w, m_clip->h),
															SDL_TEXTUREACCESS_TARGET);

	// Render the clip, from the whole sprite sheet held in m_texture
	RenderTextureToTexture(m_texture, clippedTexture, m_clip);

	// Set the new clip as the main texture
	m_texture = clippedTexture;

	// Re-enable new texture
	EnableBlending();

	// Set the size of the new texture, before the clip is nullified.
	m_size = Dimensions(m_clip->w, m_clip->h);
	// Nullify clip pointer
	m_clip = nullptr;
}

bool Texture_Wrapper::ShouldRender(void) const 
{ 
	bool imageValid = (m_texture != nullptr);
	bool renderToTarget = (m_target) ? !m_target->IsStatic() : true;

	return (imageValid && renderToTarget);
}


void Texture_Wrapper::RenderToTarget(Coordinates pos) const
{
	if (m_texture != nullptr)
	{
		// Render to m_target. If m_target is nullptr, SDL still renders direct to the Window.
		if (m_target) RenderToTexture(pos);
		else		  RenderToWindow(pos);
	}
	else throw runtime_error("Cannot render a nullptr texture.");
}

void Texture_Wrapper::RenderToTexture(Coordinates pos) const
{
	// Get the streamed texture of the target
	SDL_Texture* targetTexture = m_target->GetTexture();

	// Create destination rectangle using pos and size
	SDL_Rect destinationRect = RectFromXY(pos, m_size);
	
	// Render to it
	RenderTextureToTexture(m_texture, targetTexture, m_clip, &destinationRect);
}

void Texture_Wrapper::RenderToWindow(Coordinates pos) const
{
	// Create destination rectangle using pos and size
	SDL_Rect destinationRect = RectFromXY(pos, m_size);
	RenderTextureToWindow(m_texture, m_clip, &destinationRect);
}



	/**** TextureTarget ****/

TextureTarget::TextureTarget(Dimensions size, bool staticImage) 
	: Texture_Wrapper(SSID_NULL, nullptr, staticImage)
{ 
	// Check for an invalid size
	if (size.Contains(0)) 
		throw std::runtime_error("Cannot have a size with width or height of 0.");
	
	// Redefine the m_image in a manner befitting a TextureTarget
	DefineTextureForTargetting(size);

	if (!staticImage) g_renderer->AddTarget(this); 
}

void TextureTarget::DefineTextureForTargetting(Dimensions size)
{
	// Texture Streamers are targetted by others, so have Target access.
	m_texture = CreateTexture(size, SDL_TEXTUREACCESS_TARGET);
	// No m_clip, so the size must be set via argument.
	m_size = size;
	
	EnableBlending();
}

void TextureTarget::Clear(void)
{
	SDL_Rect alphaWashRect = {0, 0, m_size.x, m_size.y};
	RenderRectToTexture(m_texture, &alphaWashRect, 0x00, 0x00, 0x00, 0x00);
}