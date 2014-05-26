#pragma once
#include "Tools.h"

class TextureTarget;

class Texture_Wrapper
{
public:
	// Create a texture from a sprite sheet file
	Texture_Wrapper(const SSID ssid, SDL_Rect* clip, const bool staticClip);

	virtual ~Texture_Wrapper(void);

	// Add a Texture Streamer for this to stream its texture toward
	void SetStreamer(TextureTarget* streamer) { m_target = streamer; }

	// Change the image's clip
	void SetClip(SDL_Rect* newClip) { if (!m_staticClip) m_clip = newClip; else throw std::runtime_error("Cannot change the clip of a static texture"); }

	// Render texture onto renderer-pointer's target
	void RenderToTarget(Coordinates pos) const;

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
	SDL_Surface* m_source;
	bool m_staticClip;

	// Load the source surface that this Texture comes from
	void LoadSource(SSID ssid);

	// Load the texture from the Source, using the renderer
	void CreateTextureFromSource(void);

	// Load the texture from the Source, using the renderer
	void CreateTextureForTargetting(void);

	void RenderToTexture(Coordinates pos) const;
	void RenderToWindow(Coordinates pos) const;
};

typedef Texture_Wrapper Image;
typedef Texture_Wrapper Texture;

class TextureTarget : public Texture_Wrapper
{
public:
	// Create a texture with NULL source
	TextureTarget(void) : Texture_Wrapper(SSID_NULL, NULL, false) {}
};

typedef TextureTarget ImageTarget;
