#include "Texture_Wrapper.h"
#include "Resources.h"
#include "ToolKit.h"
#include "Renderer_Wrapper.h"
#include "Camera.h"

Texture_Wrapper::Texture_Wrapper(const SSID ssid, SDL_Rect* clip, const bool staticClip) 
	: m_clip(clip), m_staticClip(staticClip), m_target(nullptr)
{
	// Create the texture, based on its SSID. If SSID_NULL, do not load a texture image.
	DefineTextureFromFile(ssid);

	// If it's a static clip, and only a section of the sprite sheet is to be used, Clip the Texture (permanently). 
	if (m_staticClip && m_texture && m_clip)
	{
	if ( SDL_QueryTexture(m_texture, 0, 0, 0, 0) != 0)
		printf("Invalid Texture!!!\n");
	}
	if (m_staticClip && m_clip) ClipTexture();
	else if ((!m_clip) && (m_texture))
	{
		// If no clip, initialise m_size using loaded texture size
		int _x = 0, _y = 0;
		SDL_QueryTexture(m_texture, 0, 0, &_x, &_y);
		m_size = Dimensions(_x, _y);
	}
}

Texture_Wrapper::Texture_Wrapper(const std::string text, TTF_Font* font, const SDL_Color color, int* pixelWrap) 
	: m_clip(nullptr), m_staticClip(true), m_target(nullptr)
{
	// Create the texture from text.
	DefineTextureFromText(text, font, color, pixelWrap);
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
	case SSID_SPEECH:
		m_texture = Resources::GetSpeechImage();
		break;
	default:
		throw runtime_error("SSID not recognised during Texture construction.");
	}
}

void Texture_Wrapper::DefineTextureFromText(const std::string text, TTF_Font* font, const SDL_Color color, int* pixelWrap)
{
	// Create a surface for the text
	SDL_Surface* textSurface;
	if (pixelWrap) textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, *pixelWrap);
	else		   textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	EnsureSuccess(textSurface);

	// Set the size based on the surface size
	m_size = Dimensions(textSurface->w, textSurface->h);

	// Create this texture from the text surface
	m_texture = CreateTexture(textSurface);

	// Free the surface
	SDL_FreeSurface(textSurface);
}

void Texture_Wrapper::EnsureValidClip(SDL_Rect* clip) const
{
	// Check that the clip is actually within the texture
	SDL_Rect imageRect = {0, 0, m_size.x, m_size.y};
	if (THROW_ERROR_ON_BAD_CLIP)
	{
		if ( !RectIsWithin(clip, &imageRect) || !clip)
			throw std::runtime_error("Trying to set the clip outside of the bounds of the image");
	}
}


void Texture_Wrapper::SetClip(SDL_Rect* newClip) 
{ 
	// Check that the clip is actually within the texture
	EnsureValidClip(newClip);

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
	if ((m_clip->w== 0) || (m_clip->h == 0))
		throw std::runtime_error("Cannot pass a clip with width or height as 0");

	// Check to see that the clip is within the image
	if (THROW_ERROR_ON_BAD_CLIP)
	{
		if ( !RectIsWithin(m_clip, m_texture) ) {
			RectIsWithin(m_clip, m_texture);
			throw std::runtime_error("The clip being initially set does not fit the sprite sheet it comes from.");
		}
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
	
	// The rectangular portion of this image to render
	SDL_Rect* screenAreaPortion = m_size > LOGICAL_SIZE ? 
								  &RectFromXY(pos*-1, LOGICAL_SIZE) : 
								  nullptr;
	
	// Blit to the entire screen
	SDL_Rect destinationRect = (m_size > LOGICAL_SIZE) ? 
								RectFromXY(0, LOGICAL_SIZE) : 
								RectFromXY(pos, m_size);

	RenderTextureToWindow(m_texture, 
						 (m_clip) ? m_clip : screenAreaPortion, 
						 &destinationRect);
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

TextureTarget::~TextureTarget(void)
{ 
	// Remove all pointers to this texture target from the renderer's list. 
	g_renderer->RemoveTarget(this); 
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