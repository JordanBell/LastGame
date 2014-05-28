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

	// Get the width and height of this image
	virtual Dimensions Size(void) const;

	bool ShouldRender(void) const { return (m_texture != NULL); }

protected:
	// The SDL_Texture that this class wraps around
	SDL_Texture* m_texture;
	// Pointer to any TextureStreamers
	const TextureTarget* m_target;
	// The clip from which this object renders
	SDL_Rect* m_clip;

private:
	bool m_staticClip;

	// Load the source texture from the SSID
	void CreateTextureFromFile(SSID ssid);

	// Create a texture formatted for targetting
	void CreateTextureForTargetting(void);

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
	/* Create a texture with NULL source
		@staticImage A target with a static image does not get refreshed 
					 each time Clear() is called in the g_renderer wrapper.
	*/
	TextureTarget(bool staticImage = false);
};

typedef TextureTarget ImageTarget;
