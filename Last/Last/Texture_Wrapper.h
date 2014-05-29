#pragma once
#include "Tools.h"

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

	virtual ~Texture_Wrapper(void);

	// Add a Texture Streamer for this to stream its texture toward
	void SetTarget(TextureTarget* target) { m_target = target; }

	// Change the image's clip
	void SetClip(SDL_Rect* newClip) { if (!m_staticClip) m_clip = newClip; else throw std::runtime_error("Cannot change the clip of a static texture"); }

	// Render texture onto renderer-pointer's target
	void RenderToTarget(Coordinates pos) const;

	// Clear the texture to transparency
	void Clear(void);

	// Return the raw SDL Texture
	SDL_Texture* GetTexture(void) const { return m_texture; }

	// Return whether or not this is static
	const bool IsStatic(void) const { return m_staticClip; }

	// Get the width and height of this image
	Dimensions Size(void) const { return m_size; }

	// Whether or not this Texture is fit for rendering
	bool ShouldRender(void) const;

protected:
	// The SDL_Texture that this class wraps around
	SDL_Texture* m_texture;
	// Pointer to any TextureStreamers
	const TextureTarget* m_target;
	// The clip from which this object renders
	SDL_Rect* m_clip;
	// The state of the clip's updateability.
	bool m_staticClip;

	Dimensions m_size;

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
	TextureTarget(Dimensions size = Dimensions(512, 320), bool staticImage = false);

private:
	// Create a texture formatted for targetting
	void DefineTextureForTargetting(Dimensions size);
};

typedef TextureTarget ImageTarget;
