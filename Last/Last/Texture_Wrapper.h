#pragma once
#include "Tools.h"
#include "Config.h"

class TextureTarget;

class Texture_Wrapper
{
public:
	/* Create a texture from a sprite sheet file
		@staticClip A Texture with a static clip will save space, as it 
					doesn't need to save its entire sprite sheet, but 
					just the section from the initially specified clip.
	*/
	Texture_Wrapper(const SSID ssid, SDL_Rect* clip, const bool staticClip);

	virtual ~Texture_Wrapper(void) { SDL_DestroyTexture(m_texture); }

	// Add a Texture Streamer for this to stream its texture toward
	void SetTarget(TextureTarget* target) { m_target = target; }

	// Change the image's clip
	void SetClip(SDL_Rect* newClip);

	// Render texture onto renderer-pointer's target
	void RenderToTarget(Coordinates pos) const;

	// Return the raw SDL Texture
	SDL_Texture* GetTexture(void) const { return m_texture; }

	// Return whether or not this is static
	const bool IsStatic(void) const { return m_staticClip; }

	// Get the width and height of this image
	Dimensions Size(void) const { return m_size; }

	// Whether or not this Texture is fit for rendering
	bool ShouldRender(void) const;

protected:
	
	SDL_Texture* m_texture; // The SDL_Texture that this class wraps around
	const TextureTarget* m_target; // Pointer to any TextureStreamers
	SDL_Rect* m_clip; // The clip from which this object renders
	bool m_staticClip; // The state of the clip's updateability.
	Dimensions m_size; // This image's size

	// Set the TextureBlendMode to SDL_BLENDMODE_BLEND
	inline void EnableBlending(void) { SDL_SetTextureBlendMode(GetTexture(), SDL_BLENDMODE_BLEND); }

private:
	// Load the source texture from the SSID
	void DefineTextureFromFile(SSID ssid);

	// Clip the texture, if its clip is static, and release the clip
	void ClipTexture(void);

	void RenderToTexture(Coordinates pos) const;
	void RenderToWindow(Coordinates pos) const;
};

typedef Texture_Wrapper Image;
typedef Texture_Wrapper Texture;

class TextureTarget : public Texture_Wrapper
{
public:
	/* Create a texture with nullptr source
		@staticImage A target with a static image does not get refreshed 
					 each time Clear() is called in the g_renderer wrapper.
	*/
	TextureTarget(Dimensions size = LOGICAL_SIZE, bool staticImage = false);
	~TextureTarget(void);

	// Clear the texture to transparency
	void Clear(void);

private:
	// Create a texture formatted for targetting
	void DefineTextureForTargetting(Dimensions size);
};

typedef TextureTarget ImageTarget;
